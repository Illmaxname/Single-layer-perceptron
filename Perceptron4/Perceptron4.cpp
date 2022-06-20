#include <iostream>
#include <ctime>
using namespace std;

const int ROWS = 10;
const int COLS = 15;

void FillArrWeights(int w[ROWS][COLS]) {
	srand(time(0));
	//Заполнение массива весов
	for (int count = 0; count < ROWS; count++) {

		for (int in_count = 0; in_count < COLS; in_count++) {
			int r_num = rand() % 10;
			w[count][in_count] = r_num;
		}
	}
}

void FillXArray(int arr[ROWS][COLS]) {
	for (int count = 0; count < ROWS; count++) {

		for (int in_count = 0; in_count < COLS; in_count++) {
			int r_num = rand() % 2;
			arr[count][in_count] = r_num;
		}
	}
}

void Training(int xArr[ROWS][COLS], int wArr[ROWS][COLS], int targetCount) {

	int tSum = 0;
	int maxSum = 0;
	for (int count = 0; count < ROWS; count++) {

		int sum = 0;
		for (int in_count = 0; in_count < COLS; in_count++) {
			sum += wArr[count][in_count] * xArr[targetCount][in_count];
		}
		if (count != targetCount && sum >= maxSum) {
			maxSum = sum;

		}
		if (count == targetCount)tSum = sum;
	}
	for (int count = 0; count < ROWS; count++) {

		int sum = 0;
		for (int in_count = 0; in_count < COLS; in_count++) {
			sum += wArr[count][in_count] * xArr[targetCount][in_count];
		}
		if (sum == maxSum && count != targetCount) {
			for (int inn_count = 0; inn_count < COLS; inn_count++) {
				if (xArr[targetCount][inn_count] == 1) {
					wArr[count][inn_count]--;
				}
			}
		}
		else if (sum < maxSum && count == targetCount) {
			for (int inn_count = 0; inn_count < COLS; inn_count++) {
				if (xArr[targetCount][inn_count] == 1) {
					wArr[targetCount][inn_count]++;
				}
			}
		}
	}
}

void SecTrain(int xArr[ROWS][COLS], int wArr[ROWS][COLS], int targetCount) {

	int tSum = 0;
	int maxSum = 0;
	bool fErr = 0;
	while (fErr == 0) {

		for (int count = 0; count < ROWS; count++) {

			int sum = 0;
			for (int in_count = 0; in_count < COLS; in_count++) {
				sum += wArr[count][in_count] * xArr[targetCount][in_count];
			}
			if (count != targetCount && sum >= maxSum) {
				maxSum = sum;

			}
			if (count == targetCount) {
				tSum = sum;
				maxSum = sum;
			}
		}
		if (maxSum == tSum)fErr = 1;
		else {
			Training(xArr, wArr, targetCount);
		}
	}

}

int Test(int xArr[ROWS][COLS], int wArr[ROWS][COLS], int *TARGET) {
	int errors = 0;
	for (int targetCount = 0; targetCount < 3; targetCount++) {
		int visited[ROWS] = { 0 };
		int count = 0;
		int num;
		int num_array[ROWS];

		//Уникальное рандомное число
		while (count < ROWS) {
			num = rand() % ROWS;

			if (visited[num] == 0) {
				visited[num] = 1;
				num_array[count++] = num;
			}
		}
		int tSum = 0;
		for (int colCount = 0; colCount < COLS; colCount++) {
			tSum += wArr[TARGET[targetCount]][colCount] * xArr[TARGET[targetCount]][colCount];
		}
		for (int count = 0; count < ROWS; count++) {

			int sum = 0;
			for (int in_count = 0; in_count < COLS; in_count++) {
				sum += wArr[count][in_count] * xArr[TARGET[targetCount]][in_count];

			}
			if (sum >= tSum && count != TARGET[targetCount]) {
				errors++;
				//cout << "error " << targetCount << count << endl;
			}
			else if (sum < tSum && count == TARGET[targetCount]) {
				errors++;
				//cout << "error " << targetCount << count << endl;
			}
		}
	}
	return errors;
}

void Disruptions(int xArr[ROWS][COLS], int disruptions, int *TARGET) {
	for (int count = 0; count < 3; count++) {

		int visited[COLS] = { 0 };
		int counter = 0;
		int num;
		int num_array[COLS];

		//Уникальное рандомное число
		while (counter < COLS) {
			num = rand() % COLS;

			if (visited[num] == 0) {
				visited[num] = 1;
				num_array[counter++] = num;
			}
		}
		for (int i = 0; i < disruptions; i++) {

			if (xArr[TARGET[count]][num_array[i]] == 1)
				xArr[TARGET[count]][num_array[i]] = 0;
			else if (xArr[TARGET[count]][num_array[i]] == 0)
				xArr[TARGET[count]][num_array[i]] = 1;
		}
	}
}

void ArrCopy(int arr1[ROWS][COLS], int arr2[ROWS][COLS]) {
	for (int count = 0; count < ROWS; count++) {
		for (int incount = 0; incount < COLS; incount++) {
			arr1[count][incount] = arr2[count][incount];
		}
	}
}

void PrintArr(int arr[ROWS][COLS]) {
	for (int count = 0; count < ROWS; count++) {
		for (int in_count = 0; in_count < COLS; in_count++) {
			cout << arr[count][in_count] << "  ";
		}
		cout << endl;
	}
}

int main() {
	int TARGET[3] = { 4,5,6 };
	for (int count = 0; count < 3; count++) {
		cout << "Target " << count + 1 << " = " << TARGET[count] << endl;
	}
	int weights[ROWS][COLS];
	FillArrWeights(weights);
	int weights2[ROWS][COLS];
	

	cout << "W array: " << endl;
	PrintArr(weights);

	//Массив признаков на вход
	int x[ROWS][COLS];
	FillXArray(x);
	int x2[ROWS][COLS];
	ArrCopy(x2, x);

	cout << "X array: " << endl;
	PrintArr(x);

	//Внесение помех и тренировка
	int trainCount = 500;
	int disruptions1 = 2;
	Disruptions(x, disruptions1, TARGET);
	for (int i = 0; i < trainCount; i++) {
		for (int targetCount = 4; targetCount < 7; targetCount++) {
			Training(x, weights, targetCount);
		}
	}
	for (int i = 4; i < 7; i++) {
		SecTrain(x, weights, i);
	}
	ArrCopy(x, x2);
	
	disruptions1 = 14;
	Disruptions(x, disruptions1, TARGET);

	for (int i = 0; i < trainCount; i++) {
		for (int targetCount = 4; targetCount < 7; targetCount++) {
			Training(x, weights,  targetCount);
		}
	}
	for (int i = 4; i < 7; i++) {
		SecTrain(x, weights, i);
	}
	ArrCopy(x, x2);
	disruptions1 = 1;
	Disruptions(x, disruptions1, TARGET);

	for (int i = 0; i < trainCount; i++) {
		for (int targetCount = 4; targetCount < 7; targetCount++) {
			Training(x, weights, targetCount);
		}
	}
	for (int i = 4; i < 7; i++) {
		SecTrain(x, weights, i);
	}
	ArrCopy(x, x2);
	disruptions1 = 15;
	Disruptions(x, disruptions1, TARGET);

	for (int i = 0; i < trainCount; i++) {
		for (int targetCount = 4; targetCount < 7; targetCount++) {
			Training(x, weights,  targetCount);
		}
	}
	for (int i = 4; i < 7; i++) {
		SecTrain(x, weights, i);
	}
	ArrCopy(x, x2);
	
	

	for (int i = 0; i < trainCount; i++) {
		for (int targetCount = 4; targetCount < 7; targetCount++) {
			Training(x, weights, targetCount);
		}
	}
	for (int i = 4; i < 7; i++) {
		SecTrain(x, weights, i);
	}
	ArrCopy(weights2, weights);

	//Тестирование
	bool flag = 0;
	int testCount = 1;
	cout << fixed;
	cout.precision(2);
	int errors;
	int disruptions = 1;
	Disruptions(x, disruptions, TARGET);
	double accuracy = 0;
	while (flag == 0) {
		errors = 0;
		for (int i = 0; i < testCount; i++) {
			errors += Test(x, weights2, TARGET);

		};

		accuracy = (double)((testCount * 30) - errors) / (testCount * 30);
		if (accuracy < 0.9) {
			for (int i = 0; i < trainCount; i++) {
				for (int targetCount = 4; targetCount < 7; targetCount++) {
					Training(x, weights2, targetCount);
				}
			}
		}
		else flag = 1;
	}
	cout << endl << errors;
	cout << endl << "Accuracy(1): " << accuracy << endl;

	ArrCopy(weights2, weights);
	ArrCopy(x, x2);
	disruptions = 2;
	Disruptions(x, disruptions, TARGET);
	flag = 0;
	while (flag == 0) {
		errors = 0;
		for (int i = 0; i < testCount; i++) {
			errors += Test(x, weights2, TARGET);
		}	
		accuracy = (double)((testCount * 30) - errors) / (testCount * 30);
		if (accuracy < 0.9) {
			for (int i = 0; i < trainCount; i++) {
				for (int targetCount = 4; targetCount < 7; targetCount++) {
					Training(x, weights2, targetCount);
				}
			}
		}
		else flag = 1;
	}
	cout << endl << errors;
	cout << endl << "Accuracy(2): " << accuracy << endl;
	ArrCopy(weights2, weights);
	ArrCopy(x, x2);
	disruptions = 14;
	Disruptions(x, disruptions, TARGET);
	flag = 0;
	while (flag == 0) {
		errors = 0;
		for (int i = 0; i < testCount; i++) {
			errors += Test(x, weights2, TARGET);
		}
		
		accuracy = (double)((testCount * 30) - errors) / (testCount * 30);
		if (accuracy < 0.9) {
			for (int i = 0; i < trainCount; i++) {
				for (int targetCount = 4; targetCount < 7; targetCount++) {
					Training(x, weights2, targetCount);
				}
			}			
		}
		else flag = 1;
	}
	cout << endl << errors;
	cout << endl << "Accuracy(14): " << accuracy << endl;
	ArrCopy(weights2, weights);
	ArrCopy(x, x2);
	disruptions = 15;
	Disruptions(x, disruptions, TARGET);
	flag = 0;
	while (flag == 0) {
		errors = 0;
		for (int i = 0; i < testCount; i++) {
			errors += Test(x, weights2, TARGET);
		}
		
		accuracy = (double)((testCount * 30) - errors) / (testCount * 30);
		if (accuracy < 0.9) {
			for (int i = 0; i < trainCount; i++) {
				for (int targetCount = 4; targetCount < 7; targetCount++) {
					Training(x, weights2, targetCount);
				}
			}			
		}
		else flag = 1;
	}
	cout << endl << errors;
	cout << endl << "Accuracy(15): " << accuracy << endl;

	ArrCopy(x, x2);

	flag = 0;
	while (flag == 0) {
		errors = 0;
		for (int i = 0; i < testCount; i++) {
			errors += Test(x, weights, TARGET);
		}
		if (errors != 0) {
			for (int i = 0; i < trainCount; i++) {
				for (int targetCount = 4; targetCount < 7; targetCount++) {
					Training(x, weights, targetCount);
				}
			}
			for (int i = 4; i < 7; i++) {
				SecTrain(x, weights, i);
			}
		}
		else flag = 1;
	}
	cout << endl << "main errors: " << errors << endl;

	//Вывод обученного массива весов
	cout << endl << "Res weight array: " << endl;
	PrintArr(weights);

	return 0;
}