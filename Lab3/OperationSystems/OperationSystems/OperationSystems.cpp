#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string MOORE_MACHINE_TYPE = "Mr";
const string MEALY_MACHINE_TYPE = "Ml";

struct CommonParams {
    string machineType;
    int stateNumber = 0;
    int inputSymbolNumber = 0;
    int outputSignalNumber = 0;
};

struct MachineState {
    int outputSignal = 0;
    int outputState = 0;
};

vector<vector<MachineState>> ReadMachineMatrix(CommonParams params)
{
    vector<vector<MachineState>> machineMatrix;
    for (int rowIndex = 0; rowIndex < params.inputSymbolNumber; rowIndex++)
    {
        vector<MachineState> row;
        for (int valueIndex = 0; valueIndex < params.stateNumber + params.outputSignalNumber; valueIndex++)
        {
            if (valueIndex < params.stateNumber)
            {
                MachineState state;
                cin >> state.outputState;
                row.push_back(state);
            }
            else
            {
                cin >> row[valueIndex - params.stateNumber].outputSignal;
            }
        }
        machineMatrix.push_back(row);
    }
}


CommonParams ReadCommonParams() {
    CommonParams params;
    cin >> params.machineType >> params.stateNumber >> params.inputSymbolNumber >> params.outputSignalNumber;
}

matrix

int main()
{
    auto commonParams = ReadCommonParams();
    auto matrix = ReadMachineMatrix(commonParams);
    
}