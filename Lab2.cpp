#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

const double PI = 3.141592653589793;
const double dt = 0.1; 

struct Vector2 {
    double x, y;
    Vector2(double x = 0, double y = 0) : x(x), y(y) {}
};

class Student {
public:
    Vector2 position;
    double angle; 
    double V;
    double timeSinceLastTurn;
    double N;

    Student(double x, double y, double V, double N)
        : position(x, y), V(V), N(N), timeSinceLastTurn(0) {
        angle = ((double)rand() / RAND_MAX) * 2 * PI;
    }

    void update(double dt) {
        timeSinceLastTurn += dt;
        if (timeSinceLastTurn >= N) {
            angle = ((double)rand() / RAND_MAX) * 2 * PI;
            timeSinceLastTurn = 0;
        }
        position.x += V * cos(angle) * dt;
        position.y += V * sin(angle) * dt;
    }
};

class Studentka {
public:
    double angle; 
    double V, R;
    Vector2 center;
    Vector2 position;

    Studentka(double centerX, double centerY, double R, double V)
        : center(centerX, centerY), R(R), V(V), angle(0) {
        updatePosition();
    }

    void update(double dt) {
        double circumference = 2 * PI * R;
        double angularSpeed = V / R;
        angle += angularSpeed * dt;
        updatePosition();
    }

private:
    void updatePosition() {
        position.x = center.x + R * cos(angle);
        position.y = center.y + R * sin(angle);
    }
};

int main() {
    srand(time(0));

    const int numStudents = 5;
    const int numStudentky = 3;
    const double V = 1.0; 
    const double N = 3.0; 
    const double R = 5.0; 

    std::vector<Student> students;
    std::vector<Studentka> studentky;

    for (int i = 0; i < numStudents; ++i) {
        students.emplace_back(rand() % 10, rand() % 10, V, N);
    }
    for (int i = 0; i < numStudentky; ++i) {
        studentky.emplace_back(0.0, 0.0, R, V); 
    }

    const double totalTime = 20.0;
    for (double t = 0; t < totalTime; t += dt) {
        std::cout << "Time: " << t << " seconds\n";
        for (int i = 0; i < numStudents; ++i) {
            students[i].update(dt);
            std::cout << "Student " << i << ": (" << students[i].position.x << ", " << students[i].position.y << ")\n";
        }
        for (int i = 0; i < numStudentky; ++i) {
            studentky[i].update(dt);
            std::cout << "Studentka " << i << ": (" << studentky[i].position.x << ", " << studentky[i].position.y << ")\n";
        }
        std::cout << "-------------------------------\n";
    }

    return 0;
}
