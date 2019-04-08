#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;
using namespace chrono;

template <typename T>
void print(T ** edges_matrix, int cities);
void fill_edges_length(int ** edges_matrix, int cities);
void visit(int ** ants, int ** edges_matrix, int i, int j);
void print_ants(int ** ants, int N, int cities);
void fill_sera(float ** ants_sera, int cities);
void start(int ** ants, int ** edges_matrix, float ** ants_sera, int cities, int N, int iterations);
int choice(int ** ants, int ** edges_matrix, float ** ants_sera, int cities,  int current_ant, int a, int b, int q, int p);
int zero_ants(int ** ants, int N, int cities);

int main()
{
    int N = 8; //кол-во муравьев, лучше быть равным кол-ву городов
    int cities = 8; // кол-во городов
    int iterations = 8; //кол-во итераций
    int ** edges_matrix = new int* [cities];
    float ** ants_sera = new float* [cities];
    int ** length = new int* [cities];
    int ** ants = new int* [N];
    for (int i = 0; i < N; i++)
    {
        ants[i] = new int [cities];
        for (int j = 0; j < cities; j++)
            ants[i][j] = -1;
    }
    
    
    fill_edges_length(edges_matrix, cities);
    fill_sera(ants_sera, cities);
    print(edges_matrix, cities);
    print(ants_sera, cities);
    
    start(ants, edges_matrix, ants_sera, cities, N, iterations);
    //visit(ants, 0, 1, cities);
    //print_ants(ants, N, cities);
	return 0;
	
}



void start(int ** ants, int ** edges_matrix, float ** ants_sera, int cities, int N, int iterations)
{
    //visit(ants, 0, 2);
    //visit(ants, 0, 7);
    int length = 0;
    int min_length = 100;
    int min_j = 0;
    //цикл по времени
    for (int j = 0; j < iterations; j++)
    {
        //цикл по муравьям
        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < cities; k++)
            {
                //i = current_ant переход на след город
                int temp_i = choice(ants, edges_matrix, ants_sera, cities, k, 1, 1, 1, 1);
                visit(ants, edges_matrix, k, temp_i);
            }
            //sera_change(ants_sera, current_ant, temp_i, q, p, edges_matrix);
            print_ants(ants, N, cities);
            length = zero_ants(ants, N, cities);
            if (length < min_length)
            {
                min_j = j;
                min_length = length;
            }
            cout << "конец " << i << " муравья, длина пути: " << length << endl <<"Минимальная длина пути: "<< min_length << endl << "Количество времени для нахождения миниммального пути: " << min_j << endl;
        }
    }
}

int choice(int ** ants, int ** edges_matrix, float ** ants_sera, int cities,  int current_ant, int a, int b, int q, int p)
{
    //a, b - степени
    //q, p - коэффициенты
    float * choice_array = new float [cities];
    
    float vision;
    float result;
    float all_result = 0;
    //0 - не был
    //-1 - был
    for (int i = 0; i < cities; i++)
    {
        if ((ants[current_ant][i] == -1) && (edges_matrix[current_ant][i] != 0))
        {
            choice_array[i] = edges_matrix[current_ant][i];
            //теперь в массив choice_array для каждого эл-та внести вероятность прохода по этому пути
            vision = 1 / choice_array[i];
            all_result += (pow(ants_sera[current_ant][i], a) * pow(vision, b));
            //cout << endl << pow(ants_sera[current_ant][i], a) << endl;
        }
        else
            choice_array[i] = -1;
        //cout << choice_array[i] << " ";
        //cout << "YATYT" << i;
    }
    //cout << endl;
    
    
    //cout << all_result << endl;
    for (int i = 0; i < cities; i++)
    {
        if (choice_array[i] != -1)
        {
            vision = 1 / choice_array[i];
            result = (pow(ants_sera[current_ant][i], a) * pow(vision, b)) / all_result;
            choice_array[i] = result;
            //cout << vision << " " << choice_array[i] << " " << all_result << " "<< pow(edges_matrix[current_ant][i], a) << " "<< pow(vision, b) << endl;
        }
    }
    /*
    for (int i = 0; i < cities; i++)
    {
        cout << choice_array[i] << " ";
    }
    cout << endl;
     */
    //Ищем путь по которому пойдем
    std::default_random_engine generator;
    float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    int temp_i = -1;
    float min = 2;
    for (int i = 0; i < cities; i++)
        if ((choice_array[i] != -1) && (fabs(random - choice_array[i]) < min))
        {
            min = random - choice_array[i];
            temp_i = i;
        }
    //индекс города в который пойдем
    //cout << temp_i << endl;
    //sera_change(ants_sera, current_ant, temp_i, q, p, edges_matrix);
    
    return temp_i;
}



int zero_ants(int ** ants, int N, int cities)
{
    int length = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < cities; j++)
        {
            if (ants[i][j] != -1)
                length += ants[i][j];
            ants[i][j] = -1;
        }
    }
    return length;
}

//не закончен, доработать
void sera_change(float ** ants_sera, int i, int j, float q, float p, int ** edges_matrix)
{
    //for (int i = 0; i < cities; i++)
    //{
        
    //}
    //Q - параметр, соразмерный длине кратчайшего пути.
    //p - коэффициент испарения
    float delta_t = q / edges_matrix[i][j];
    //for (int i = 0; i < N)
    float t = (1 - p) * ants_sera[i][j] + delta_t;
}


void print_ants(int ** ants, int N, int cities)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < cities; j++)
        {
            cout << ants[i][j] << " ";
        }
        cout << endl;
    }
    //cout << endl;
}

void visit(int ** ants, int ** edges_matrix, int i, int j)
{
    //i - из какого города
    //j - в какой город
    //ants[i] = new int [1]
    //int j = 0;
    ants[i][j] = edges_matrix[i][j];
}

template <typename T>
void print(T ** edges_matrix, int cities)
{
    int j = 0;
	for (int i = 0; i < cities; i++)
    {
        for (int j = 0; j < cities; j++)
        {
            cout << edges_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void fill_edges_length(int ** edges_matrix, int cities)
{
    for (int i = 0; i < cities; i++)
    {
        edges_matrix[i] = new int [cities];
    }
    edges_matrix[0][0] = 0;
    edges_matrix[0][1] = 1;
    edges_matrix[0][2] = 0;
    edges_matrix[0][3] = 0;
    edges_matrix[0][4] = 0;
    edges_matrix[0][5] = 0;
    edges_matrix[0][6] = 0;
    edges_matrix[0][7] = 3;
    
	edges_matrix[1][0] = 1;
	edges_matrix[1][1] = 0;
    edges_matrix[1][2] = 2;
    edges_matrix[1][3] = 4;
    edges_matrix[1][4] = 0;
    edges_matrix[1][5] = 0;
    edges_matrix[1][6] = 0;
    edges_matrix[1][7] = 0;
	//edges_matrix[2] = new int [4];
    edges_matrix[2][0] = 0;
    edges_matrix[2][1] = 2;
    edges_matrix[2][2] = 0;
    edges_matrix[2][3] = 6;
    edges_matrix[2][4] = 10;
    edges_matrix[2][5] = 2;
    edges_matrix[2][6] = 0;
    edges_matrix[2][7] = 0;
	//edges_matrix[3] = new int [6];
    edges_matrix[3][0] = 0;
    edges_matrix[3][1] = 4;
    edges_matrix[3][2] = 6;
    edges_matrix[3][3] = 0;
    edges_matrix[3][4] = 0;
    edges_matrix[3][5] = 3;
    edges_matrix[3][6] = 0;
    edges_matrix[3][7] = 0;
	//edges_matrix[4] = new int [3];
    edges_matrix[4][0] = 0;
    edges_matrix[4][1] = 0;
    edges_matrix[4][2] = 10;
    edges_matrix[4][3] = 0;
    edges_matrix[4][4] = 0;
    edges_matrix[4][5] = 6;
    edges_matrix[4][6] = 0;
    edges_matrix[4][7] = 0;
	//edges_matrix[5] = new int [3];
    edges_matrix[5][0] = 0;
    edges_matrix[5][1] = 0;
    edges_matrix[5][2] = 2;
    edges_matrix[5][3] = 3;
    edges_matrix[5][4] = 6;
    edges_matrix[5][5] = 0;
    edges_matrix[5][6] = 3;
    edges_matrix[5][7] = 1;
	//edges_matrix[6] = new int [4];
    edges_matrix[6][0] = 0;
    edges_matrix[6][1] = 0;
    edges_matrix[6][2] = 0;
    edges_matrix[6][3] = 0;
    edges_matrix[6][4] = 0;
    edges_matrix[6][5] = 3;
    edges_matrix[6][6] = 0;
    edges_matrix[6][7] = 2;
	//edges_matrix[7] = new int [5];
    edges_matrix[7][0] = 3;
    edges_matrix[7][1] = 0;
    edges_matrix[7][2] = 0;
    edges_matrix[7][3] = 0;
    edges_matrix[7][4] = 0;
    edges_matrix[7][5] = 1;
    edges_matrix[7][6] = 2;
    edges_matrix[7][7] = 0;
}

void fill_sera(float ** ants_sera, int cities)
{
    for (int i = 0; i < cities; i++)
    {
        ants_sera[i] = new float [cities];
    }
    ants_sera[0][0] = 0.1;
    ants_sera[0][1] = 0.1;
    ants_sera[0][2] = 0.1;
    ants_sera[0][3] = 0.1;
    ants_sera[0][4] = 0.1;
    ants_sera[0][5] = 0.1;
    ants_sera[0][6] = 0.1;
    ants_sera[0][7] = 0.1;
    
    ants_sera[1][0] = 0.1;
    ants_sera[1][1] = 0.1;
    ants_sera[1][2] = 0.1;
    ants_sera[1][3] = 0.1;
    ants_sera[1][4] = 0.1;
    ants_sera[1][5] = 0.1;
    ants_sera[1][6] = 0.1;
    ants_sera[1][7] = 0.1;
    //ants_sera[2] = new int [4];
    ants_sera[2][0] = 0.1;
    ants_sera[2][1] = 0.1;
    ants_sera[2][2] = 0.1;
    ants_sera[2][3] = 0.1;
    ants_sera[2][4] = 0.1;
    ants_sera[2][5] = 0.1;
    ants_sera[2][6] = 0.1;
    ants_sera[2][7] = 0.1;
    //ants_sera[3] = new int [6];
    ants_sera[3][0] = 0.1;
    ants_sera[3][1] = 0.1;
    ants_sera[3][2] = 0.1;
    ants_sera[3][3] = 0.1;
    ants_sera[3][4] = 0.1;
    ants_sera[3][5] = 0.1;
    ants_sera[3][6] = 0.1;
    ants_sera[3][7] = 0.1;
    //ants_sera[4] = new int [3];
    ants_sera[4][0] = 0.1;
    ants_sera[4][1] = 0.1;
    ants_sera[4][2] = 0.1;
    ants_sera[4][3] = 0.1;
    ants_sera[4][4] = 0.1;
    ants_sera[4][5] = 0.1;
    ants_sera[4][6] = 0.1;
    ants_sera[4][7] = 0.1;
    //ants_sera[5] = new int [3];
    ants_sera[5][0] = 0.1;
    ants_sera[5][1] = 0.1;
    ants_sera[5][2] = 0.1;
    ants_sera[5][3] = 0.1;
    ants_sera[5][4] = 0.1;
    ants_sera[5][5] = 0.1;
    ants_sera[5][6] = 0.1;
    ants_sera[5][7] = 0.1;
    //ants_sera[6] = new int [4];
    ants_sera[6][0] = 0.1;
    ants_sera[6][1] = 0.1;
    ants_sera[6][2] = 0.1;
    ants_sera[6][3] = 0.1;
    ants_sera[6][4] = 0.1;
    ants_sera[6][5] = 0.1;
    ants_sera[6][6] = 0.1;
    ants_sera[6][7] = 0.1;
    //ants_sera[7] = new int [5];
    ants_sera[7][0] = 0.1;
    ants_sera[7][1] = 0.1;
    ants_sera[7][2] = 0.1;
    ants_sera[7][3] = 0.1;
    ants_sera[7][4] = 0.1;
    ants_sera[7][5] = 0.1;
    ants_sera[7][6] = 0.1;
    ants_sera[7][7] = 0.1;
}
