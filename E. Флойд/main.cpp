#include<iostream>
#include<vector>
#include<cmath>
struct MatrixGraph {
    explicit MatrixGraph(int VCount);
    ~MatrixGraph() = default;
    void AddEdge(int from, int to, double weight);
    int VCount() const;
    void GetNextVertices(int vertex, std::vector<double>& vertices) const;
private:
    void OllFalse();
    void MakeMatrix(int VerticesCount);
    std::vector<std::vector<double>> Matrix;
};

void MatrixGraph::MakeMatrix(int VerticesCount)
{
    Matrix.resize(VerticesCount);
    for(int i = 0 ; i < VerticesCount; ++i)
    {
        Matrix[i].resize(VerticesCount);
    }
}

void MatrixGraph::OllFalse()                        //заполняем всё минус единицами
{
    for(int i = 0; i < VCount(); ++i)
    {
        for(int j = 0; j < VCount(); ++j)
        {
            Matrix[i][j] = -1;
        }
    }
}

MatrixGraph::MatrixGraph(int VCount)                //конструкток
{
    MakeMatrix(VCount);
    OllFalse();
}

int MatrixGraph::VCount() const
{
    return Matrix.size();
}

void MatrixGraph::AddEdge(int from, int to, double weight)
{
    Matrix[from][to] = weight;
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<double>& vertices) const
{
    for(int i = 0; i < VCount(); ++i)
    {
        vertices.push_back(Matrix[vertex][i]);
    }
}

std::vector<std::vector<double>> Floid(MatrixGraph& graph, double inf)
{
    int N = graph.VCount();                                             //число вершин
    std::vector<std::vector<double>>len(N, std::vector<double>(0));
    for(int i = 0; i < N; ++i)
    {
        graph.GetNextVertices(i, len[i]);                   //считываем данные из графа
    }
    for(int k = 0; k < N; ++k)                              //прохождение из одной вершины до другой через k - ую
    {
        for(int i = 0; i < N; ++i)                      //проходим по всем вершинам из которых выходим
        {
            for(int j = 0; j < N; ++j)                  //по всем вершинам в которые входим
            {
                len[i][j] = std::min(len[i][j], len[i][k] + len[k][j]);         //если пройти через эту вершину выгодно, то идём
            }
        }
    }
    return len;
}

int main()
{
    int N = 0;
    std::cin >> N;
    MatrixGraph graph(N);
    double inf = 0;
    for(int i = 0; i < N; ++i)                              //читаем граф
    {
        for(int j = 0; j < N; ++j)
        {
            double weight = 0;
            std::cin >> weight;
            graph.AddEdge(i, j, weight);                            //добавляем вершину
            inf = std::max(inf, std::abs(weight));                  //считаем самое дорогое ребро
        }
    }
    inf = 2 * inf * N;                                              //считаем что такое бесконечность
    std::vector<std::vector<double>>answer = Floid(graph, inf);     //запускаем флойда
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)                                  //выводим ответ
        {
            std::cout << answer[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

