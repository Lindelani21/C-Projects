/**
 * @file main.cpp
 * @brief Calculates whether or not basketballs will make it in the hoop based on specified measurements over time.
 *
 * This program reads inn data from a csv file about distance data  and predicts whether
 * basketball shots will land in the hoop. It uses geometric dimensions and arithmetics(i think)
 * to evaluate which balls will end up going in the hoop
 *
 * @author Ragedi Maubane Lindelani Lethabo
 * Completed using Eclipse
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <cmath>

using namespace std;

/*
 * The object that i'm gonna use to store each ball's data
 */
struct Ball {
    double x; // Horizontal position
    double y; // Vertical position
    //Going forth, x will refer to horizontal and y will be for vertical
};


// Constants for the hoop and sensors
const double HOOP_X = 12.4;
const double HOOP_Y = 3.05;
const double HOOP_RADIUS = 0.4572;
const double BALL_RADIUS = 0.24;
const double SENSOR1_X = 0;
const double SENSOR1_Y = 0;
const double SENSOR2_X = 12.4;
const double SENSOR2_Y = 0;


/* calcPosition
 * Function to calculate ball's position using sensor distances
 *
 * @param, dist1. The distance for sensor1
 * @param, didt2. The distance for sensor2
 *
 * Assuming that each ball's trajectory will be vertical because it is a 2D field
 */
Ball calcPosition(double dist1, double dist2) {
	
	double knownDistances= ( (dist1 * dist1) -  (dist2 * dist2) ) - ((SENSOR1_X *  SENSOR1_X) + (SENSOR2_X * SENSOR2_X)); // distances of the ball from sensors

    double horizontalX = 2* (SENSOR2_X -  SENSOR1_X); 
 
    double x = knownDistances / horizontalX; //x coordinate
    double y = sqrt(dist1 * dist1 - x * x); //y coordinate

    return {x, y};
}


/* evaluateGoal
 * Function to check if the ball trajectory intersects the hoop
 *
 * @param, vector<Ball>& trajectory. It is a read-only reference to a vector of Ball objects,
 *         it should pass the ball's trajectory efficiently without modifying it.
 */
bool evaluateGoal(const vector<Ball>& trajectory) {

    for (const auto& point: trajectory) {

        double distance = sqrt ( pow(point.x  - HOOP_X, 2) + pow(point.y - HOOP_Y,2) ); //gonna be used to check for intersection 

        cout <<"Checking trajectory point (" <<point.x<< ", " <<point.y<< ") -> Distance to hoop: " <<distance<< endl;

        if (distance <= HOOP_RADIUS) {
            return true; // Ball scores
        }
    }

    return false;
}

int main() {

    ifstream file("basketball.csv"); // Open the CSV file

    if ( !file.is_open() ) {

        cerr << "Could not open file!\n Ensure that your file is in the right directory" << endl;

        return 1;
    }


    string line;
    getline(file, line); // Read and ignore the header line

    map<string, vector<pair<double, double>>> ballData;

    while (getline(file, line)) { // Read each row
        stringstream ss(line);   // Use stringstream to parse the row
        string cell;

        // Parse each value and group them by ball
        int ballNum = 1;
        while (getline(ss, cell, ',')) {
            double val1 = stod(cell); // First sensor value
            if (!getline(ss, cell, ',')) break;
            double val2 = stod(cell); // Second sensor value

            // Store data for the current ball in the vectot
            ballData["b" + to_string(ballNum)].push_back({val1, val2});
            ballNum++;
        }
    }
    file.close(); // Close the file

    // Process each ball's data
    for (auto& [ballName, measurements] : ballData) {

        cout << "\n Evaluating trajectory for " << ballName << endl;
        vector<Ball> trajectory;

        for (auto& [dist1, dist2] : measurements) {

            Ball position = calcPosition(dist1, dist2);
            trajectory.push_back(position);

            cout <<"Sensor distances (" <<dist1<< ", " <<dist2<< ") -> Ball position (" <<position.x<< ", " <<position.y<< ")\n";
        }

        // Check if the ball scores
        if (evaluateGoal(trajectory)) {
            cout << ballName << " scores!\n";
        } else {
            cout << ballName << " misses!\n";
        }
    }

    return 0;
}



