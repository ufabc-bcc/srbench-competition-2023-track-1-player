#include"DataInOut.h"
int		TerminalNumber = 0;
int		SampleNumber;
int		record_gap = 25;
vector<double>Y_train;
vector<vector<double>> X_train;
double  r2train = 0;
double  r2test = 0;
vector<pair<string,double>>expressions;

void Read(string filename) {
	ifstream inFile(filename, ios::in);
	if (!inFile.is_open()) {
		std::cout << "open file fail" << endl;
		exit(1);
	}
	string lineStr;
	char breakpoint = ',';
	getline(inFile, lineStr);
	vector<vector<double>> Data;
	int i = 0;
	while (getline(inFile, lineStr) && i < SampleNumber){
		stringstream ss(lineStr);
		string str;
		vector<double> lines;
		while (getline(ss, str, breakpoint))
		{
			lines.push_back(stod(str));
		}
		Data.push_back(lines);
		i++;
	}

	TerminalNumber = Data[0].size() - 1;
	for (int i = 0; i < SampleNumber; i++) {
		vector<double>lines;
		for (size_t j = 0; j < TerminalNumber; j++) {
			lines.push_back(Data[i][j]);
		}
		X_train.push_back(lines);
		Y_train.push_back(Data[i][TerminalNumber]);
	}
};

void output()
{
	string path = "output\\output.txt";
	ofstream mycout(path);
	mycout << "data\tacc\texpression\t\n";
	for (int i = 0; i < expressions.size(); i++) {
		mycout << i + 1 << "\t" << expressions[i].second << "\t" << expressions[i].first << endl;
	}
	mycout.close();
}

void WeightByMIC(double* probability) {
	MINE mine(0.6, 15, EST_MIC_APPROX);
	vector<double>v1, v2;

	double sum = 0;
	for (size_t i = 0; i < TerminalNumber; i++) {
		for (size_t j = 0; j < SampleNumber; j++) {
			v1.push_back(X_train[j][i]);
			v2.push_back(Y_train[j]);
		}
		mine.compute_score(&v1[0], &v2[0], v1.size());
		probability[i] = mine.mic();
		sum += probability[i];
		v1.clear();
		v2.clear();
	}
	probability[0] = probability[0] / sum;
	for (int i = 1; i < TerminalNumber; i++) {
		probability[i] = probability[i] / sum + probability[i - 1];
	}
	cout << endl;
}