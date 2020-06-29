
#include <iostream>
#include <vector>
using namespace std;

// co factor 
vector< vector<double> > getCofactor(vector< vector<double> > A, int p, int q) 
{
    int n = A.size();
    vector< vector<double> > temp;
    temp.resize(A.size()-1, std::vector<double>(A.size()-1, 0));
	int i = 0, j = 0; 

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q) 
			{
				temp[i][j++] = A[row][col]; 
				if (j == n - 1)
				{
					j = 0; 
					i++;
				}
			}
		}
	}
return temp;
}

void display(vector< vector<double> > P)
{
	for (int i = 0; i < P.size(); i++) { 
        for (int j = 0; j < P[i].size(); j++) 
            cout << P[i][j] << " "; 
        cout << endl; 
    } 
}
int determinant(vector< vector<double> > A)
{   
    int n = A.size();
	int D = 0;  // D = Determinant

	if (n == 2) 
		return ((A[0][0] * A[1][1]) - (A[1][0] * A[0][1]));

	vector< vector<double> > temp; // n X n 
    temp.resize(A.size()-1, std::vector<double>(A.size()-1, 0));
	int sign = 1;  // sign = +, -, +, -...

	for (int f = 0; f < n; f++)
	{
		temp = getCofactor(A,0,f);  // 0 Determinant 
		D += sign * A[0][f] * determinant(temp); 

		sign = -sign; // +, -, +, -...
	}

	return D; //  n X n | Determinant
}

vector< vector<double> > adjoint(vector< vector<double> > A) 
{
    vector< vector<double> > adj;
    adj.resize(A.size(), std::vector<double>(A.size(), 0));
	if (A.size() == 1)
	{
		adj[0][0] = 1;
		return adj;
	}

	int sign = 1;

	vector< vector<double> > temp; // n X n 
    temp.resize(A.size()-1, std::vector<double>(A.size()-1, 0));

	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			temp = getCofactor(A, i, j); 

			sign = ((i + j) % 2 == 0) ? 1 : -1; 

			adj[i][j] = (sign) * (determinant(temp)); // n - 1 X n - 1 
		}
	}
return adj;
}

vector< vector<double> > inverse(vector< vector<double> > A)
{
    vector< vector<double> > inv;
    inv.resize(A.size(), std::vector<double>(A.size(), 0));
	int det = determinant(A); // Determinant


	vector< vector<double> > adj;
	adj.resize(A.size(), std::vector<double>(A.size(), 0));

	adj = adjoint(A);

	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A.size(); j++)
			inv[i][j] = adj[i][j] / float(det); 


return inv;
}


// Multiply Matrices
// Function to multiply two matrix of different dimension
vector< vector<double> > multiply(vector< vector<double> > a, vector< vector<double> > b )
{
    int r1 = a.size();
    int c1 = a[0].size();
    int r2 = b.size();
    int c2 = b[0].size();
    
    vector< vector<double> > product;
    product.resize(r1, std::vector<double>(c2, 0));
	if (c1!=r2)
	{
		cout<<"Matrice input dimension is invalid!\n";
	}
	if (c1 == r2) {
    

    // multiplying 
	for(int i=0; i<r1; ++i) // r1
   		for(int j=0; j<c2; ++j) // c2
     			for(int k=0; k<c1; ++k) {   // c1
         			product[i][j]+=a[i][k]*b[k][j];
     	 }
   return product;
}
}

// Transpose
vector< vector<double> > Trans(vector< vector<double> > a)
{
    vector< vector<double> > aT;
    aT.resize(a[0].size(), std::vector<double>(a.size(), 0));
    for(int i=0; i<aT.size(); ++i) // r1
   		for(int j=0; j<aT[i].size(); ++j) // c2
   		    aT[i][j] = a[j][i];
   	
   	return aT;
}   


// Substraction of matrix
vector< vector<double> > error_s(vector< vector<double> > a, vector< vector<double> > b)
{
	int r1 = a.size();
    int c1 = a[0].size();
    int r2 = b.size();
    int c2 = b[0].size();
    vector< vector<double> > subtract;
	subtract.resize(a.size(), std::vector<double>(a[0].size(), 0));
	//if (r1==r2 && c1==c2)
	//{
		for(int i=0; i<r1 ; i++)
			for(int j=0; j<c2; j++)
				subtract[i][j] = a[i][j] - b[i][j];
	
return subtract;
	//}
	//else {
	//	cout<< " Invalid matrix for substraction";
	//}
//return subtract;
}



int main()
{
    // vector< vector<double> > A{{20,-5,-10},{-5,20,-5},{-10,-5,20}};
    // //cout<<A.size();
    // //determinant(A);
    // vector< vector<double> > G;
    // vector< vector<double> > ADJ;
    // G = getCofactor(A,0,0);
    // display(G);
    // cout << determinant(A);
    // ADJ = adjoint(A);
    // display(ADJ);
    // display(inverse(A));
    
    //Tie-set matrix
    vector< vector<double> > M {
							  {1,0,0,1,-1,0},
                              {0,1,0,0,1,-1},
                              {0,0,1,-1,0,1}
							  } ;
    
    //Impedance matrix
    vector< vector<double> > Zb{{5,0,0,0,0,0},
                              {0,10,0,0,0,0},
                              {0,0,5,0,0,0},
                              {0,0,0,10,0,0},
                              {0,0,0,0,5,0},
                              {0,0,0,0,0,5}};
                              
    //Branch Voltage matrix
    vector< vector<double> > Eb{{50},{0},{0},{0},{0},{0}};
    
	// Load impedance Zl = M*Eb*Trans(M)
    vector< vector<double> > Zl;  // Loop Impedance
    // Transpose of M
    vector< vector<double> > Mt; // Transpose of Tie-set matrix
    Mt = Trans(M);
    Zl = multiply(multiply(M,Zb),Mt);
    display(Zl);
    // Zl*Il = M*Eb => Il = inv(Zl)*M*Eb
    vector< vector<double> > Il; // Loop Current
    Il = multiply(inverse(Zl),multiply(M,Eb));
    // Ib = M*Il
	vector< vector<double> > Ib; // Branch Current
    Ib = multiply(Mt,Il);
    // Vb = Zb*Ib-Eb
    vector< vector<double> > Vb; // Branch Voltage
    vector< vector<double> > multiply_Zb_Ib;
    multiply_Zb_Ib = multiply(Zb,Ib); 
    Vb = error_s(multiply_Zb_Ib,Eb);
    // cout<<"\n\n" <<multiply_Zb_Ib.size()<<multiply_Zb_Ib[0].size();
    // cout<<"\n\n" <<Il.size()<<Il[0].size();
    
    cout<< " Branch current: \n";
    display(Ib);
    cout<< " Branch voltage: \n";
    display(Vb);
    
    
    
    return 0;
} 
