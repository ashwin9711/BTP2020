#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
/*
	Please note that every comment that starts with a '#' needs to be considered while using this code as a black box.
*/
const int k = 2;                                                                   // # k,l: dimensions of the feature map 
const int l = 1;
const int m = 9;                                                                   // # m: no. of data points
const int n1 = 7;                                                                  // # n1: no. of attributes/dimensions in the input set


// The following function is employed to calculate the coefficient when incrementing the weights of the map
float coef(int a, int b, int c, int d, int t)
{
	float n0, t0, tn, s0;
	n0 = 1.; t0 = 500000.; tn = 50000.; s0 = 1.;
	float S, S0;
	S = (a - c) * (a - c) + (b - d) * (b - d);
	S0 = s0 * exp((-1.0 * t / t0));
	if (S0 == 0 && S != 0) return 0;
	if (S0 == 0 && S == 0) return n0 * exp((-1.0 * t / tn));
	S0 *= S0;
	return exp((-1.0 * S / (2 * S0))) * n0 * exp((-1.0 * t / tn));
}

int main()
{
	float Inp[m][n1];
	float R[m][n1];
	int n;
	float temp;
	int temp1, temp2;
	srand(time(NULL));

	// # Updating the training data
	R[0][0] = 84.8;
	R[0][1] = 976.4;
	R[0][2] = 746.5;
	R[0][3] = 5;
	R[0][4] = 1;
	R[0][5] = 2;
	R[0][6] = 4.7;

	R[1][0] = 77;
	R[1][1] = 958.6;
	R[1][2] = 2003;
	R[1][3] = 7;
	R[1][4] = 1;
	R[1][5] = 4;
	R[1][6] = 7.6;

	R[2][0] = 43.7;
	R[2][1] = 378.4;
	R[2][2] = 1636.4;
	R[2][3] = 4;
	R[2][4] = 4;
	R[2][5] = 10;
	R[2][6] = 5.2;

	R[3][0] = 34.9;
	R[3][1] = 379.5;
	R[3][2] = 752.1;
	R[3][3] = 4;
	R[3][4] = 0;
	R[3][5] = 3;
	R[3][6] = 5.2;

	R[4][0] = 47.3;
	R[4][1] = 598.4;
	R[4][2] = 645.4;
	R[4][3] = 6;
	R[4][4] = 0;
	R[4][5] = 5;
	R[4][6] = 33.4;

	R[5][0] = 60.2;
	R[5][1] = 699.7;
	R[5][2] = 797.3;
	R[5][3] = 7;
	R[5][4] = 1;
	R[5][5] = 5;
	R[5][6] = 18.1;

	R[6][0] = 61;
	R[6][1] = 656.8;
	R[6][2] = 1907.5;
	R[6][3] = 4;
	R[6][4] = 1;
	R[6][5] = 9;
	R[6][6] = 3.5;

	R[7][0] = 32.5;
	R[7][1] = 384.5;
	R[7][2] = 1830.6;
	R[7][3] = 4;
	R[7][4] = 0;
	R[7][5] = 9;
	R[7][6] = 3.3;

	R[8][0] = 29.4;
	R[8][1] = 317.9;
	R[8][2] = 641.7;
	R[8][3] = 3;
	R[8][4] = 0;
	R[8][5] = 16;
	R[8][6] = 2.5;
	
	//Normalising data
	float x;
	for (int j = 0; j < n1; j++)
	{
		x = 0;
		for (int i = 0; i < m; i++)
		{
			if (R[i][j] > x) x = R[i][j];
		}
		for (int i = 0; i < m; i++)
		{
			R[i][j] = (R[i][j] / x) * 100.;
		}

	}
	int a1[n1];
	FILE* fp;
	fp = fopen("output.txt", "w");

	/*  # if p1= 25 which is 1*2^(1-1) + 1*2^(4-1) + 1*2^(5-1). 
	   Then the following algorithm would consider attributes/dimensions {1,4,5} from the set {1,2,3,4,5,6,7...n1} for SOM
	   For all 7 attributes at the same time, please change this to (int p1=127; p1<127 ;p1++)
	*/
	for (int p1 = 1; p1 <= 127; p1++)
	{
		int c;
		int q = 0;
		int r;
		for (int i = 0; i < 7; i++) { a1[i] = 0; }
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n1; j++) { Inp[i][j] = 0; }
		}
		c = p1;
		n = 0;
		while (c != 0)
		{
			r = c % 2;
			c = c / 2;
			if (r == 1) { a1[n] = q; n++; }
			q++;
		}



		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				q = a1[j];
				Inp[i][j] = R[i][q];
			}
		}

		float o[500][2];
		int length = 0;

		// # this loop determines the number of times each combination is fed through SOM
		for (int p = 0; p < 500; p++)
		{
			//randomising the order of the inputs in Inp[m][n] for increased effectiveness	
			for (int i = 0; i < 3 * m; i++)
			{
				temp1 = rand() % m;
				temp2 = rand() % m;
				for (int j = 0; j < n; j++)
				{
					temp = Inp[temp1][j];
					Inp[temp1][j] = Inp[temp2][j];
					Inp[temp2][j] = temp;
				}
			}

			// a[k][l][n1]: Feature map with dimensions k,l and n1 no. of weights
			float a[k][l][n1];

			// Assigning small random values to the map for initialisation
			for (int t1 = 0; t1 < k; t1++)
			{
				for (int t2 = 0; t2 < l; t2++)
				{
					for (int t3 = 0; t3 < n1; t3++)
					{
						a[t1][t2][t3] = (rand() % 10) / 10.;
					}
				}
			}

			// k1,l1: coordinates of the winning neuron
			int k1, l1;
			float tempmin;
			float coeff;

			// SOM algorithm over all the training data given
			for (int t = 0; t < m * 200000; t++)
			{
				int k1 = 0, l1 = 0;
				temp = 0;
				float tempmin = 0;

				// Determination of the winning neuron		
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < l; j++)
					{
						temp = 0;
						for (int n2 = 0; n2 < n; n2++)
						{
							temp += ((Inp[t % m][n2] - a[i][j][n2]) * (Inp[t % m][n2] - a[i][j][n2]));
						}
						if (i == 0 && j == 0) tempmin = temp;
						else if (temp < tempmin) { tempmin = temp; k1 = i; l1 = j; }
					}
				}

				// Incrementing weights of all the neurons
				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < l; j++)
					{
						coeff = coef(i, j, k1, l1, t);
						for (int n2 = 0; n2 < n; n2++)
						{
							a[i][j][n2] += coeff * (Inp[t % m][n2] - a[i][j][n2]);
						}

					}
				}
			}
 
			int t3;
			float o1 = 0;
			float o2;
			int oc;
			for (int t = 0; t < m; t++)
			{
				k1 = 0; l1 = 0;
				temp = 0;
				tempmin = 0;

				for (int i = 0; i < k; i++)
				{
					for (int j = 0; j < l; j++)
					{
						temp = 0;
						for (int n1 = 0; n1 < n; n1++)
						{
							temp += ((R[t][n1] - a[i][j][n1]) * (R[t][n1] - a[i][j][n1]));
						}
						if (i == 0 && j == 0) tempmin = temp;
						else if (temp < tempmin) { tempmin = temp; k1 = i; l1 = j; }
					}
				}
				if (t == 0) oc = k1;
				o2 = t;
				if (k1 != oc) o1 += pow(2, o2);

			}
			int sign = 0;
			for (int i = 0; i < length; i++)
			{
				if (o[i][0] == o1) { o[i][1]++; sign = 1; }
			}
			if (sign == 0)
			{
				o[length][0] = o1;
				o[length][1] = 1;
				length++;
			}
		}
		fprintf(fp,"%d-> ", p1);
		for (int i = 0; i < n; i++)
		{
			fprintf(fp, "%d ", a1[i] + 1);
		}
		fprintf(fp,":\n ");

		for (int i = 0; i < length; i++)
		{

			q = 0;
			r = 10;
			c = o[i][0];
			while (c != 0)
			{
				r = c % 2;
				c = c / 2;
				fprintf(fp,"%d ", r);
				q++;
			}
			while (q < m)
			{
				fprintf(fp,"0 ");
				q++;
			}
			fprintf(fp,"-> %.0f\n", o[i][1]);
		}
		fprintf(fp,"\n\n");
	}
	/* # Output format:
					25-> 1 4 5:
					0 0 1 1 0 0 1 1 1 -> 60
					0 0 0 1 1 0 0 1 1 -> 40
					This implies, for the combination of attributes {1,4,5} the first classification mentioned occurred 60 times
					and the other, 40.
					Read the classification as follows. 
					Eg. For 0 0 1 1 0 0 1 1 1
					R[0], R[1],           R[4], R[5]                  belongs to group 1
							   R[2], R[3],           R[6], R[7], R[8] belongs to group 2
	*/
	fclose(fp);
	return 0;

}