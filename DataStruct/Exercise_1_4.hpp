#ifndef EXERCISE_1_4_HPP
#define EXERCISE_1_4_HPP

template <typename T>
void print_array(T** x, const int rows, const int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << x[i][j] << " ";
        }
        std::cout << '\n';
    }
}

template <typename T>
void print_array(T** x, const int rows, const T* row_size)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < *(row_size + i); j++)
        {
            std::cout << x[i][j] << " ";
        }
        std::cout << '\n';
    }
}

template <typename T>
void make_2_array(T** & x, const int number_of_rows, const int number_of_columns)
{
    x = new T*[number_of_rows]{nullptr};
    for (int i = 0; i < number_of_rows; i++)
    {
        x[i] = new T [number_of_columns];
    }
}

template <typename T>
void make_2_array(T** & x, const int number_of_rows, const T* row_size)
{
    x = new T*[number_of_rows];
    for (int i = 0; i < number_of_rows; i++)
    {
        if (*(row_size + i) <= 0)
        {
            throw std::invalid_argument("row size must be positive");
        }
        x[i] = new T [*(row_size + i)];
    }
}

template <typename T>
void init_2_array(T** & x, const int number_of_rows, const T* row_size, const T value)
{
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j < *(row_size + i); j++)
            x[i][j] = value;
}

template <typename T>
void init_2_array(T** & x, const int number_of_rows, const int number_of_columns, const T value)
{
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j < number_of_columns; j++)
            x[i][j] = value;
}

template <typename T>
void delete_2_array(T** & x, const int number_of_rows)
{
    for (int i = 0; i < number_of_rows; i++)
        delete [] x[i];
    delete [] x;
    x = nullptr;
}

template <typename T>
T* change_length_1d(T* & x, const int old_length, const int new_length)
{
    if (new_length <= 0)
    {
        delete [] x;
        x = nullptr;
        T* temp = nullptr;
        return temp;
    }

    T* temp = new T[new_length];
    for (int i = 0; i < std::min(new_length, old_length); i++)
        temp[i] = x[i];
    if (new_length > old_length)
    {
        for (int i = old_length; i < new_length; i++)
            temp[i] = 0;
    }
    delete [] x;
    x = nullptr;
    return temp;
}

template <typename T>
T** change_length_2d(T** & x, const int old_rows, const int old_columns, const int new_rows, const int new_columns)
{
    if (new_rows <= 0 || new_columns <= 0)
    {
        for (int i = 0; i < old_rows; i++)
        {
            delete [] x[i];
        }
        delete [] x;
        x = nullptr;
        T** temp = nullptr;
        return temp;
    }

    T** temp = new T*[new_rows];
    for (int i = 0; i < new_rows; i++)
    {
        temp[i] = new T [new_columns];
    }

    for (int i = 0; i < std::min(new_rows, old_rows); i++)
    {
        for (int j = 0; j < std::min(new_columns, old_columns); j++)
        {
            temp[i][j] = x[i][j];
        }
    }

    if (new_rows > old_rows)
    {
        for (int j = 0; j < new_columns; j++)
        {
            for (int i = old_rows; i < new_rows; i++)
            {
                temp[i][j] = 0;
            }
        }
    }

    if (new_columns > old_columns)
    {
        for (int i = 0; i < new_rows; i++)
        {
            for (int j = old_columns; j < new_columns; j++)
            {
                temp[i][j] = 0;
            }
        }
    }


    for (int i = 0; i < old_rows; i++)
    {
        delete [] x[i];
    }
    delete [] x;
    x = nullptr;
    return temp;
}

#endif
