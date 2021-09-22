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
에라스토테네스의 체를 사용한다고 할 때 우리가 위의 동적계획법을 통해 얻고자 하는 것은 결국 소수인 i에 의해 k까지의 숫자중 지워지는 것의 수이다.
우리는 현재 i를 키워나가며 refinement를 하는것이다. 이 때 i로 인해 제거될 숫자들을 생각하면 이전에 지워지지 않은 숫자들이므로 최소 prime factor가 
i가 되어야 한다. 즉 k/m 이하의 자연수중 m보다 큰 prime factor를 가지지 않는 숫자를 찾아 그 개수만큼 빼주면 되는 것이다. 이 때 우리는 k/i 번째 dp 값
에 현재 저장되어 있을 숫자가 k/i에서 i-1까지 동적계획법을 실행한 결과, 즉 k/i 이하의 수 중에서 소수 혹은 m-1보다 큰 least prime factor를 가지는 수임을
알고있다. 따라서 여기서 i-1 이하의 소수를 빼준다면 우리가 원하던  k/m 이하의 자연수중 m보다 큰 prime factor를 가지지 않는 숫자의 수를 얻게 되는 것이다.
위의 수식은 이러한 논리에 의해 나온 수식이며 이 논리에 따라 1~sqrt(N), N/sqrt(N)~N/1 에 관한 체크만 이루어지면 되므로 dp 배열 역시 그에 맞추어 선언된 것이다.
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

	cout << "소수의 개수 :"  << numberOfPrime << endl;
	double endTime = clock();
	double elapsedTime = (double)(endTime - startTime);
	cout << "프로그램 수행 시간 : " << elapsedTime << endl;
	return 0;
}