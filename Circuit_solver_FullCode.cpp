#include <iostream>
#include <vector>
#include<iterator>
using namespace std;

vector< vector<double> > getCofactor(vector< vector<double> > A, int p, int q)  // Co-factor of a square matrix; (p,q) element of matrix
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

void display(vector< vector<double> > P)  // To display 2D array (For testing only) 
{
	for (int i = 0; i < P.size(); i++) { 
        for (int j = 0; j < P[i].size(); j++) 
            cout << P[i][j] << " "; 
        cout << endl; 
    } 
}

void show(vector< vector<double> > P,int n)  // Show Final output i.e voltage (at n=1) & current (at n=2)
{
	switch(n)
	{
	    case 1:   
	            for (int i = 0; i < P.size(); i++) { 
                    for (int j = 0; j < P[i].size(); j++) 
                        cout << "Branch "<<i+1<< ": "<<P[i][j] << " "; 
                    cout << endl; 
	            }
            break;
        
        case 2:
            
                for (int i = 0; i < P.size(); i++) { 
                    for (int j = 0; j < P[i].size(); j++) 
                        cout << "Edge "<<i+1<< ": "<<P[i][j] << " "; 
                    cout << endl; 
                }
            break;
    } 
}

int determinant(vector< vector<double> > A)    // Returns determinant of a matrix
{   
    int n = A.size();
	int D = 0;  // D =  Determinant

	if (n == 2) 
		return ((A[0][0] * A[1][1]) - (A[1][0] * A[0][1]));

	vector< vector<double> > temp;
    temp.resize(A.size()-1, std::vector<double>(A.size()-1, 0));
	int sign = 1;  // sign = +, -, +, -.... 

	for (int f = 0; f < n; f++)
	{
		temp = getCofactor(A,0,f); 
		D += sign * A[0][f] * determinant(temp); 

		sign = -sign; 
	}

	return D; 
}

vector< vector<double> > adjoint(vector< vector<double> > A)   // Returns adjoint of matrix using utility function determinant() & getCofactor()
{
    vector< vector<double> > adj;
    adj.resize(A.size(), std::vector<double>(A.size(), 0));
	if (A.size() == 1) 
	{
		adj[0][0] = 1;
		return adj;
	}

	int sign = 1;

	vector< vector<double> > temp; 
    temp.resize(A.size()-1, std::vector<double>(A.size()-1, 0));

	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			temp = getCofactor(A, i, j); 

			sign = ((i + j) % 2 == 0) ? 1 : -1;

			adj[i][j] = (sign) * (determinant(temp)); 
		}
	}
return adj;
}

vector< vector<double> > inverse(vector< vector<double> > A)   // Returns inverse of matrix using function deterninant() and adjoint()
{
    vector< vector<double> > inv;
    inv.resize(A.size(), std::vector<double>(A.size(), 0));
	int det = determinant(A); 

	vector< vector<double> > adj;
	adj.resize(A.size(), std::vector<double>(A.size(), 0));

	adj = adjoint(A); 

	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A.size(); j++)
			inv[i][j] = adj[i][j] / float(det); 

return inv;
}

vector< vector<double> > multiply(vector< vector<double> > a, vector< vector<double> > b )   // Function for multiplying two matrices of different dimension
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

vector< vector<double> > Trans(vector< vector<double> > a)  // Returns transpose of a matrix 
{
    vector< vector<double> > aT;
    aT.resize(a[0].size(), std::vector<double>(a.size(), 0));
    for(int i=0; i<aT.size(); ++i) // r1
   		for(int j=0; j<aT[i].size(); ++j) // c2
   		    aT[i][j] = a[j][i];
   	
   	return aT;
}   

vector< vector<double> > error_s(vector< vector<double> > a, vector< vector<double> > b)  // To subtract two matrices of same dimension
{
	int r1 = a.size();
    int c1 = a[0].size();
    int r2 = b.size();
    int c2 = b[0].size();
    vector< vector<double> > subtract;
	subtract.resize(a.size(), std::vector<double>(a[0].size(), 0));
	
		for(int i=0; i<r1 ; i++)
			for(int j=0; j<c2; j++)
				subtract[i][j] = a[i][j] - b[i][j];
	
return subtract;

}

vector< vector<double> > InsertData(vector< vector<double> > alpha, int q)  // Utility function to take data input from user; q=1 for tie-set matrix i/p; q=2 for Impedance; q=3 for voltage
{
    int j =0;
    int r = alpha.size();
    int c = alpha[0].size();
    vector< vector<double> > output;
	output.resize(r, std::vector<double>(c, 0));
    switch(q)
    {
    case 1:
            cout<<"Enter tie-set matrix data :\n";
            
            for (int i=0; i<r; i++)
            {
                for(int j=0;j<c;j++)
                {
                    cout<<"Loop-"<<i+1<<" Edge-"<<j+1<<": ";
                    cin>> alpha[i][j];
                }
            }
            return alpha;
            break;

    case 2:
            cout<<"Enter impedance matrix:\n";
            
            for (int i=0; i<r; i++)
            {
                    cout<<"Edge-"<<i+1<<": ";
                    cin>> alpha[i][i];
            }
            return alpha;
            break;
    
    case 3:
            cout<<"Enter volage matrix\n";
            
            for (int i=0; i<r; i++)
            {
                for(int j=0;j<c;j++)
                {
                    cout<< "Edge-"<<j+1<<": ";
                    cin>> alpha[i][j];
                }
            }
            return alpha;
            break;
    }
}

void display_adj(vector<int> adj_list[], int v){    // Display Adjacency matrix (Simple circuit); Display Graph.
	for(int i = 0; i<v; i++){
		cout << i << "--->";
		vector<int> :: iterator it;
		for(it = adj_list[i].begin(); it != adj_list[i].end(); ++it){
			cout << *it << " ";
		}
		cout << endl;
	}
}

void create_matrix(vector<int>adj_matrix[], int nodes) // create graph according to user input
{
    for(int i=1; i<nodes; i++)
    {
        adj_matrix[0].push_back(i);
        if(i < nodes-1)
        {
            adj_matrix[i].push_back(i+1);
        }
    }
    
}

void MST(vector<int>adj_matrix[],vector<int>mst[])   // Generate minimum spanning tree of graph
{
    vector<int> :: iterator it;
		for(it = adj_matrix[0].begin(); it != adj_matrix[0].end(); ++it){
			
			mst[0].push_back(*it);
		}
}

vector<vector<double>> tie_set(vector<vector<double>>M)   // Using MST detecting fundamental loops and finding generating tie-set matrix
{
    int l = M.size();
    int e = M[0].size();
    M[0][0]=1;
    M[0][1]=1;
    M[0][2]=1;
    for(int i =1; i<l;i++)
    {
       M[i][(2*i)]=-1;
       M[i][(2*i)+1]=1;
       M[i][(2*i)+2]=1;
    }
    return M;
}

void display_int(vector< vector<int> > P)   // Display 2D array of "int" type
{
	for (int i = 0; i < P.size(); i++) { 
        for (int j = 0; j < P[i].size(); j++) 
            cout << P[i][j] << " "; 
        cout << endl; 
    } 
}

int main()
{
    int nodes, edges;
    cout<<" ***  Cicuit Simulator Using Graph Theory and Network Topology  ***\n\n";
    cout<< " Choose one of the option : \n";
    cout<<" 1. Simple cicuit (Auto Solve)\n";
    cout<< " 2. Complex Circuit\n\n";
    cout<<" Instructions: \n I. The mandatory information you needed to feed are voltage and impedance of every edge. \n ";
	cout<< "II. If it's complex ciruit option you have choosen then feed Tie-set matrix along with two matrices mentioned above.\n";
    cout<< "III. Tie-set matrix is matrix of fundamental loops and its current direction.\n ";
    cout<<"\n"<<"Enter your choice: ";
    int choice;
    cin>> choice;
    cout<<"\nYou have choosen Option  "<<choice<<"\n\n";
    vector< vector<double> > M; // Tie-set matrix
    vector< vector<double> > Zb; // Branch impedance matrix
    vector< vector<double> > Eb; // Branch voltage source matrix
    vector< vector<double> > Zl;  // Loop Impedance matrix
    vector< vector<double> > Mt; // Transpose of Tie-set matrix
    vector< vector<double> > Il; // Loop Current matrix
    vector< vector<double> > Ib; // Branch Current matrix
    vector< vector<double> > Vb; // Branch Voltage
    vector< vector<double> > multiply_Zb_Ib; // matrix to store Zb*Ib
    
    switch(choice) 
    {
        case 1:    // For simple circuit option
        {
            
            int n;
            cout<< "Nodes in circuit including ground: ";
            cin>>n;
            int l = n-2;
            int e = 2*n-3;
    
            vector<int>adj_matrix[n]; // Adjacency list
            vector<int>mst[n]; // Minimum spanning tree list
            
            M.resize(l, std::vector<double>(e, 0)); // Resizing tie-set matrix according to user input
            M = tie_set(M);
            create_matrix(adj_matrix, n); // Generating graph
            MST(adj_matrix,mst);  // Finding MST
            
            Zb.resize(e, std::vector<double>(e, 0)); //  Resizing impedance matrix according to user input
            Zb = InsertData(Zb,2);  // User input for impedance matrix
            
            Eb.resize(1, std::vector<double>(e, 0)); //  Resizing voltage source matrix according to user input
            Eb = InsertData(Eb, 3); // User input for voltage source
            
            // Network Topology Implementation
            // Formula : Load impedance Zl = M*Eb*Trans(M)
        
            Mt = Trans(M); // Transpose of M
            Zl = multiply(multiply(M,Zb),Mt);
            
            // Formula : Zl*Il = M*Eb => Il = inv(Zl)*M*Eb
            
            Il = multiply(inverse(Zl),multiply(M,Eb));
            
            // Formula: Ib = M*Il   (Final Output)
        	
            Ib = multiply(Mt,Il);
            
            // Formula: Vb = Zb*Ib-Eb  (Final Output)
            
            multiply_Zb_Ib = multiply(Zb,Ib); 
            Vb = error_s(multiply_Zb_Ib,Eb);
            
            cout<< " Branch current: \n";
            show(Ib,2);
            cout<< " Branch voltage: \n";
            show(Vb,1);
        }
            break;
        
        case 2:     // For Complex Circuit
        {
            
            int loops;
            cout<< "Number of fundamental loops:";
            cin>>loops;
            cout<<"\n"<<"Number of edges: ";
            cin>>edges;
            
            M.resize(loops, std::vector<double>(edges, 0));   // Resizing tie-set matrix according to user input
            M = InsertData(M,1);  // User input for tie-set matrix
            
            Zb.resize(edges, std::vector<double>(edges, 0)); //  Resizing impedance matrix according to user input
            Zb = InsertData(Zb,2);  // User input for impedance matrix
            
            Eb.resize(1, std::vector<double>(edges, 0)); //  Resizing voltage source matrix according to user input
            Eb = InsertData(Eb, 3);  // User input for voltage source
            
            
            // Network Topology Implementation
            // Formula : Load impedance Zl = M*Eb*Trans(M)
        
            Mt = Trans(M); // Transpose of M
            Zl = multiply(multiply(M,Zb),Mt);
            
            // Formula : Zl*Il = M*Eb => Il = inv(Zl)*M*Eb
            
            Il = multiply(inverse(Zl),multiply(M,Eb));
            
            // Formula: Ib = M*Il   (Final Output)
        	
            Ib = multiply(Mt,Il);
            
            // Formula: Vb = Zb*Ib-Eb  (Final Output)
            
            multiply_Zb_Ib = multiply(Zb,Ib); 
            Vb = error_s(multiply_Zb_Ib,Eb);
            
            cout<< " Branch current: \n";
            show(Ib,2);
            cout<< " Branch voltage: \n";
            show(Vb,1);
        }
            break;
    
    }
    return 0;
} 
