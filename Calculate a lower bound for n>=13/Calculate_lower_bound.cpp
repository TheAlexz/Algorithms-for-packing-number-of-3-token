#include <bits/stdc++.h>

using namespace std; 

#define watch(x) cout << (#x) << " is: " << x << endl;
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

typedef long long int lli;
typedef unsigned long long int ulli;
typedef vector<long long int> vlli;

//How many nodes does the F3(Pn) graph have?
const ulli F3Pn_nodes = 286;

//Which node do you want in the second position?
int second_position_node = 0;

//What's the file path of the GDM_F3(Pn) file?
string filename = "C:/Users/Joel9/Documents/Investigacion Grafos/Packing and 3token graphs/GDM/GDM_F3(P13).csv";

ulli GDM[F3Pn_nodes][F3Pn_nodes];

// Function to fill the GDM array with the values of the .csv file
void readFromFile(const string& FileName) {
    ifstream take(FileName);

    // The GDM array is filled with the values of the .csv file
    string line;
    ulli i = 0;
    while (getline(take, line)) {
        stringstream ss(line);
        string cell;
        ulli j = 0;
        while (getline(ss, cell, ',')) {
            GDM[i][j] = stoi(cell);
            j++;
        }
        i++;
    }

}


//Read the csv file 
void read_record()
{
    // Call readFromFile function to read the csv file and fill the GDM array
    readFromFile(filename);    
    
    fstream fin;
  
    // Open an existing file
    fin.open(filename);    
  
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    vector<ulli> rowint;
    

    vector<ulli> sumintprobables;

    vector<tuple<ulli, ulli, ulli>> packing_max;
    vector<tuple<ulli, ulli, ulli>> triplet_max;

    string line, word, temp;
    ulli number, sum=0, count=0, rowpmax=0;
    ulli countrow=0, countcolum=0, count_triplet=0, num_packing_max=0;  
    

    time_t start, end;

    time(&start);
    
  
    // read an entire row and
    // store it in a string variable 'line'  
    while (fin >> line) {

        sum=0; countcolum=0; count_triplet=0;
  
        row.clear();
        rowint.clear();
        packing_max.clear();
        packing_max.clear();      

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
  
            // add all the column data
            // of a row to a vector
            row.push_back(word);
            number = stoi(word);
            rowint.push_back(number);


            //Begin filling the triplet_sorted vector with only the values that are greater than or equal to 3 or equal to 0
            if( number >= 3 or number == 0 ){            


                if(number == 0){
                    //Inserts at the beginning the vertex with distance 0, that is, the vertex n where n is the current row
                    packing_max.insert(packing_max.begin(), make_tuple(number, countrow, countcolum));
                }
                else{
                    
                    packing_max.push_back(make_tuple(number, countrow, countcolum));
                }
                sum++;
                count_triplet++;
            }
            countcolum++;
        }
        
        cout << endl;


        sumintprobables.push_back(sum);


        if(second_position_node == 0){
            //No need to do anything
        }
        if(second_position_node == 1){
            //Erase all the vertices before the node with ID = 1 (keeping the first position node, that is, the node of the current row)
            for(int i=0; i<3; i++){
                if(get<2>(packing_max[i]) == 0){
                    packing_max.erase(packing_max.begin() + i);
                    break;
                }
            }
        }
        else if(second_position_node == 2){
            //Erase all the vertices before the node with ID = 2 (keeping the first position node, that is, the node of the current row)
            for(int i=0; i<4; i++){
                if(get<2>(packing_max[i]) == 0 or get<2>(packing_max[i]) == 1){
                    packing_max.erase(packing_max.begin() + i);
                    i--;
                }
            }
        }
        else if(second_position_node == 3){
            //Erase all the vertices before the node with ID = 3 (keeping the first position node, that is, the node of the current row)
            for(int i=0; i<5; i++){
                if(get<2>(packing_max[i]) == 0 or get<2>(packing_max[i]) == 1 or get<2>(packing_max[i]) == 2){
                    packing_max.erase(packing_max.begin() + i);
                    i--;
                }
            }
        }        

        ulli column_sel=0, column_act=0;

        
        //Algorithm to keep only the vertices that have a distance greater than or equal to 3 from each other
        for (ulli i = 1; i < packing_max.size()-1; i++){

            for (ulli j = i+1; j < packing_max.size(); j++){

                column_sel = get<2>(packing_max[i]);

                column_act = get<2>(packing_max[j]);


                if(  GDM[column_sel][column_act] < 3  ){

                    packing_max.erase(packing_max.begin() + j);

                    j--;
                } 
                
            }
        }
        
        watch(countrow)


        cout << "Local maximal packing: " << packing_max.size() << endl;

        
        //If the current packing is greater than the maximum packing, then the maximum packing is updated
        num_packing_max = max(num_packing_max, ulli(packing_max.size()));
        if(num_packing_max == ulli(packing_max.size())){
            triplet_max = packing_max;
            rowpmax = countrow;
        }

        cout << "Current maximum packing: " << num_packing_max << endl;


        count++;
        countrow++;

    }
    cout << endl;

    cout << "The maximum packing set was found in the " << rowpmax << "th row" << endl;
    cout << "The cardinality of the maximum packing set is: " << num_packing_max << endl;
    

    cout << "The nodes on the maximum packing set are (ID's): ";

    int countv=0;

    for (ulli i = 0; i < triplet_max.size(); i++) {
            cout << get<2>(triplet_max[i]) ;
            if(i != triplet_max.size()-1)
                cout << ", ";  
            countv++;
    }

    cout << endl << endl;

    time(&end);

    // Calculating total time taken by the program.
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
        << time_taken << setprecision(10);
    cout << " sec " << endl;
    
}

int main(){

    fastIO

    read_record();


    return 0;
}
