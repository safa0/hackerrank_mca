#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);
static constexpr uint8_t MAX_EXPENSE_VALUE = 200;

int findIndexOfValueFromCumulativeVector(int index, std::vector<int>& frequencyCounter)
{
    const auto& it = std::lower_bound(frequencyCounter.begin(), frequencyCounter.end(),index);
    return it - frequencyCounter.begin();
}

int isNotifyRequired(vector<int>& A, vector<int> frequencyCounter, const int& d, int _i)
{
    int medVal = 0;
    bool retVal = false;
    //cumulative
    //TODO: get lower bound and work from there
    for (int i = 1; i < frequencyCounter.size(); ++i)
    {
        frequencyCounter[i] += frequencyCounter[i - 1];
    }

    if (d % 2 == 0)
    {
        int first = findIndexOfValueFromCumulativeVector(d / 2, frequencyCounter);
        int second = findIndexOfValueFromCumulativeVector(d / 2 + 1, frequencyCounter);
        medVal = first + second;
    }
    else
    {
        medVal = 2 * findIndexOfValueFromCumulativeVector(d / 2 + 1, frequencyCounter);
    }
    if (A[_i] >= medVal )
        return true;
    return false;
}

int activityNotifications(vector<int> A, int d)
{
    int alerts = 0;
    vector<int> frequencyCounter(MAX_EXPENSE_VALUE, 0);

    //init first full rolling window
    for (int i = 0; i < d; ++i)
    {
        ++frequencyCounter[A[i]];
    }

    for (int i = d; i < A.size(); ++i)
    {
        bool result = isNotifyRequired(A, frequencyCounter, d, i);
        if (result)
            ++alerts;

        ++frequencyCounter[A[i]];
        --frequencyCounter[A[i - d]];
    }
    return alerts;
}
int main(int argc, char* argv[])
{
    ofstream fout(getenv("OUTPUT_PATH"));

    ifstream fin;
    fin.open(argv[1]);
    if(fin.fail())
    {

        cout << "Error reading file" << std::endl;
        return 1;
    }
    string nd_temp;
    getline(fin, nd_temp);
    cout << "nd_temp: " << nd_temp << std::endl;

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);
    string expenditure_temp_temp = "";
    getline(fin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++)
    {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }
    //safa
    int result = activityNotifications(expenditure, d);
    // std::vector<int> A = {1, 0, 3,2, 1, 3, 7, 5, 100};
    // int result = activityNotifications(A, A.size() - 4);

    cout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ')
    {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos)
    {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
