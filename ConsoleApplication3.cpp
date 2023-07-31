#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<Windows.h>
#include <conio.h>
using namespace std;

struct Question {
    string question;
    vector<string> answers;
    int correctAnswer;
};

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void saveQuizToFile(const string& fileName, const vector<Question>& quiz) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& question : quiz) {
            file << question.question << endl;
            file << question.answers.size() << endl;
            for (const auto& answer : question.answers) {
                file << answer << endl;
            }
            file << question.correctAnswer << endl;
        }
        file.close();
        cout << "Quiz saved to " << fileName << endl;
    }
    else {
        cout << "Unable to open file " << fileName << " for writing." << endl;
    }
}

vector<Question> loadQuizFromFile(const string& fileName) {
    vector<Question> quiz;
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Question question;
            question.question = line;
            int numAnswers;
            file >> numAnswers;
            getline(file, line);
            for (int i = 0; i < numAnswers; i++) {
                getline(file, line);
                question.answers.push_back(line);
            }
            file >> question.correctAnswer;
            getline(file, line);
            quiz.push_back(question);
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << fileName << " for reading." << endl;
    }
    return quiz;
}

void createQuiz() {
    vector<Question> quiz;
    string quizName;

    cout << "Enter Quiz name: ";
    cin >> quizName;

    int numQuestions;
    cout << "Enter the number of questions: ";
    cin >> numQuestions;

    for (int i = 0; i < numQuestions; i++) {
        Question question;
        cout << "Question " << i + 1 << ": ";
        cin.ignore();
        getline(cin, question.question);

        int numAnswers;
        cout << "Enter the number of answers: ";
        cin >> numAnswers;
        cin.ignore();

        for (int j = 0; j < numAnswers; j++) {
            string answer;
            cout << "Answer " << j + 1 << ": ";
            getline(cin, answer);
            question.answers.push_back(answer);
        }

        cout << "Enter the correct answer (1-" << numAnswers << "): ";
        cin >> question.correctAnswer;

        quiz.push_back(question);
    }

    saveQuizToFile(quizName, quiz);
}

void startQuiz() {
    string quizName;
    cout << "Enter Quiz name: ";
    cin >> quizName;

    vector<Question> loadedQuiz = loadQuizFromFile(quizName);
    int score = 0;

    for (const auto& question : loadedQuiz) {
        cout << "Question: " << question.question << endl;
        for (int i = 0; i < question.answers.size(); i++) {
            cout << i + 1 << ": " << question.answers[i] << endl;
        }

        int answer;
        cout << "Enter your answer (1-" << question.answers.size() << "): ";
        cin >> answer;

        if (answer == question.correctAnswer) {
            score++;
        }
    }

    cout << "Result" << endl;
    cout << "Correct: " << score << endl;
    cout << "Incorrect: " << loadedQuiz.size() - score << endl;
}

int main() {
   
    srand(time(nullptr));

    char choice = '1'; 
    char key;

    do {
        system("cls");

        if (choice == '1') {
            SetColor(14);
            cout << "MENU FOR QUIZ " << endl;
            SetColor(15);
            SetColor(12); 
            cout << "1) Create Quiz" << endl;
            SetColor(15); 
            cout << "2) Start Quiz" << endl;
            cout << "3) Exit" << endl;
        }

        else if (choice == '2') {
            SetColor(14);
            cout << " MENU FOR QUIZ " << endl;
            SetColor(15);
            cout << "1) Create Quiz" << endl;
            SetColor(12); 
            cout << "2) Start Quiz" << endl;
            SetColor(15); 
            cout << "3) Exit" << endl;
        }
        else if (choice == '3') {
            SetColor(14);
            cout << " MENU FOR QUIZ "<<endl;
            SetColor(15); 
            cout << "1) Create Quiz" << endl;
            cout << "2) Start Quiz" << endl;
            SetColor(12); 
            cout << "3) Exit" << endl;
            SetColor(15); 
        }

        key = _getch();

        if (key == 13) {
            if (choice == '1') {
                SetColor(15); 
                createQuiz();
            }
            else if (choice == '2') {
                SetColor(15); 
                startQuiz();
            }
            else if (choice == '3') {
                break;
            }
        }
        else if (key == 72) {
            if (choice > '1') {
                choice--;
            }
        }
        else if (key == 80) {
            if (choice < '3') {
                choice++;
            }
        }

    } while (true);

    return 0;
}
