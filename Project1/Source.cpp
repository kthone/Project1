#include <time.h>
#include <iostream>
using namespace std;
typedef long long int ll;

ll N; //N for the number which we will count primes until
ll C; // root of N for preprocessing
bool ispr[330000]; //list indicates whether the number is prime of not
ll num_pr[330000], A[330000], B[330000]; //list for dynamic programming

//function for getting dynamic programming value
ll get_dp(ll x) {
	if (x <= C) return A[x];
	return B[N / x];
}


//function that calculates the number of primes
void dp_func(void)
{
	ll i, j;
	

	//i : number for sieve, we only need to see until C
	for (i = 2; i <= C; i++)
	{
		//ignore the case where i is not prime
		if (!ispr[i]) continue;
		//when i is prime
		//Here, k-th dp value means number of primes until k when we used erastothenes's sieve with the primes less than or equal to i
		for (j = 1; j <= C; j++)
		{
			if (N / j < i * i) break; //since we only need to see until root when finding prime numbers under certain number
			B[j] = B[j] - (get_dp(N / j / i) - num_pr[i - 1]); 
		}
		for (j = C; j >= 1; j--)
		{
			if (j < i * i) break; //since we only need to see until root when finding prime numbers under certain number
			A[j] = A[j] - (get_dp(j / i) - num_pr[i - 1]);
		}
	}
}
/*
The reason why B[j] = B[j] - (get_dp(N / j / i) - num_pr[i - 1]); and A[j] = A[j] - (get_dp(j / i) - num_pr[i - 1]);
�������׳׽��� ü�� ����Ѵٰ� �� �� �츮�� ���� ������ȹ���� ���� ����� �ϴ� ���� �ᱹ �Ҽ��� i�� ���� k������ ������ �������� ���� ���̴�.
�츮�� ���� i�� Ű�������� refinement�� �ϴ°��̴�. �� �� i�� ���� ���ŵ� ���ڵ��� �����ϸ� ������ �������� ���� ���ڵ��̹Ƿ� �ּ� prime factor�� 
i�� �Ǿ�� �Ѵ�. �� k/m ������ �ڿ����� m���� ū prime factor�� ������ �ʴ� ���ڸ� ã�� �� ������ŭ ���ָ� �Ǵ� ���̴�. �� �� �츮�� k/i ��° dp ��
�� ���� ����Ǿ� ���� ���ڰ� k/i���� i-1���� ������ȹ���� ������ ���, �� k/i ������ �� �߿��� �Ҽ� Ȥ�� m-1���� ū least prime factor�� ������ ������
�˰��ִ�. ���� ���⼭ i-1 ������ �Ҽ��� ���شٸ� �츮�� ���ϴ�  k/m ������ �ڿ����� m���� ū prime factor�� ������ �ʴ� ������ ���� ��� �Ǵ� ���̴�.
���� ������ �̷��� ���� ���� ���� �����̸� �� ���� ���� 1~sqrt(N), N/sqrt(N)~N/1 �� ���� üũ�� �̷������ �ǹǷ� dp �迭 ���� �׿� ���߾� ����� ���̴�.
*/




int main() {
	double startTime = clock();
	int numberOfPrime; 
	N = 1e9; //initialize N
	C = (ll)(sqrt(N)); //initialize C
	ispr[1] = false;
	ll i, j;

	//initialize A and B
	for (i = 1; i <= C; i++) A[i] = i - 1;
	for (i = 1; i <= C; i++) B[i] = N / i - 1;
	
	for (i = 2; i <= C; i++) ispr[i] = true;
	
	//check the prime until C using erastothenes's sieve
	for (i = 2; i <= C; i++)
	{
		if (!ispr[i]) continue; //do not consider the number which is already not the prime
		for (j = 2 * i; j <= C; j += i) ispr[j] = false; // erastothenes's sieve
	}

	//calculate number of primes until i's less than or equal to C
	for (i = 2; i <= C; i++)
	{
		num_pr[i] = num_pr[i - 1];
		if (!ispr[i]) continue;
		num_pr[i]++;
	}

	//calculate primes
	dp_func();
	
	//get the computed dp value
	numberOfPrime = get_dp(N);

	cout << "�Ҽ��� ���� :"  << numberOfPrime << endl;
	double endTime = clock();
	double elapsedTime = (double)(endTime - startTime);
	cout << "���α׷� ���� �ð� : " << elapsedTime << endl;
	return 0;
}