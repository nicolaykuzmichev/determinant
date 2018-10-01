#include <iostream>
#include <fstream>
#include <locale>
#include "matrix.h"

using namespace std;

void load_matrix_from_file(char _filename[], Matrix &_matrix)
{
	if (_matrix.get_lock_matrix() == 0)
	{
		fstream matrix_file(_filename);

		if (matrix_file.is_open())
		{
			int buff = 0;
			matrix_file >> buff >> buff;

			long double number = 0.0;

			for (int loop_row = 0; loop_row < _matrix.get_dimension_x(); loop_row++)
			{
				for (int loop_column = 0; loop_column < _matrix.get_dimension_y(); loop_column++)
				{
					matrix_file >> number;
					_matrix.set_value(loop_row, loop_column, number);
				}
			}
		}
		matrix_file.close();
	}
}

void print_matrix(ostream &stream, Matrix _matrix)
{
	if (_matrix.get_lock_matrix() == 0)
	{
		for (int loop_row = 0; loop_row < _matrix.get_dimension_x(); loop_row++)
		{
			for (int loop_column = 0; loop_column < _matrix.get_dimension_y(); loop_column++)
			{
				stream << _matrix.get_value(loop_row, loop_column) << " ";
			}
			stream << "\r\n";
		}
		stream << "\r\n";
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "DETCOUNT v3.0. Copyright(C) 2018 Кузьмичев Николай" << endl << endl;
	char working = '1';
	char filename[255] = "";

	if (filename[0] == '\0')
	{
		cout << "Введите имя файла с матрицей (в имени файла не должно быть нелатинских букв и запрещенных символов):" << endl;
		cout << ">> ";
		cin >> filename;
		cout << endl;
	}

	fstream matrix_file(filename);

	if (! matrix_file.is_open())
	{
        cout << "Файл с матрицей невозможно открыть!" << endl << endl;  
		system("pause");
		return 0;
	}
    else
    {
		int determinant_x = 0;
		int determinant_y = 0;

		matrix_file >> determinant_x >> determinant_y;
		matrix_file.close();

		Matrix matrix(determinant_x, determinant_y);
		load_matrix_from_file(filename, matrix);

		if (matrix.get_lock_matrix() == 1)
		{
			cout << "Матрица некорректна, операции запрещены!" << endl << endl;
			system( "pause" );
			return 0;
		}
		else
		{
			do
			{
			cout << "Исходная матрица: " << endl;
			print_matrix(cout, matrix);

			char action = '0';

			cout << "Выберите действие для работы с матрицей:" << endl;
			cout << "1. Подсчет определителя" << endl;
			cout << "2. Перестановка двух строк" << endl;
			cout << "3. Перестановка двух столбцов" << endl;
			cout << "4. Произведение двух матриц" << endl;
			cout << "5. Произведение матрицы на число" << endl;
			cout << "6. Сложение двух матриц" << endl;
			cout << "7. Разность двух матриц" << endl;
			cout << "8. Получение обратной матрицы из исходной" << endl;
			cout << "9. Транспонировать матрицу" << endl;
			cout << "*. Вычислить след матрицы" << endl;
			cout << "&. Вычислить ранг матрицы" << endl;
			cout << "+. Сохранить данные в файл" << endl;
			cout << ">> ";
			cin >> action;
			cout << endl;

			switch (action)
			{
				case '1':
					{
						if (matrix.get_lock_determinant() == 1)
						{
							cout << "Матрица не квадратного типа, вычислить определитель невозможно!" << endl << endl;
						}
						else
						{
							char method = '0';

							cout << "Выберите метод для подсчета определителя:" << endl;
							cout << "1. Приведение к верхнетреугольному виду методом Гаусса и произведение элементов главной диагонали" << endl;
							cout << "2. Рекурсивное разложение строк на сумму их алгебраических дополнений" << endl;
							cout << ">> ";
							cin >> method;
							cout << endl;

							switch (method)
							{
								case '1': 
									{
										long double result = matrix.count_determinant_matrix(0);
										cout << "Определитель размера " << matrix.get_dimension_x() << "x" << matrix.get_dimension_y() << " равен: " << result << " (" << long long int(floor(result + 0.5)) << ")" << endl << endl;
										break;
									}
								case '2': 
									{
										long double result = matrix.count_determinant_matrix(1);
										cout << "Определитель размера " << matrix.get_dimension_x() << "x" << matrix.get_dimension_y() << " равен: " <<result << " (" << long long int(floor(result + 0.5)) << ")" << endl << endl;
										break;
									}

								default: 
									{
										cout << "Неверный метод!" << endl << endl;
										break;
									}
							}
						}
						break;
					}
				case '2':
					{
						cout << "Введите индекс первой строки: " << endl;
						int the_first_row = 0;
						cout << ">> ";
						cin >> the_first_row;
						cout << endl;

						cout << "Введите индекс второй строки: " << endl;
						int the_second_row = 0;
						cout << ">> ";
						cin >> the_second_row;
						cout << endl;

						if (matrix.swap_rows(the_first_row, the_second_row) == -1)
						{
							cout << "Неверные индексы!" << endl << endl;
						}
						else
						{
							cout << "Полученая матрица: " << endl;
							print_matrix(cout, matrix);
						}
						break;
					}
				case '3':
					{
						cout << "Введите индекс первого столбца: " << endl;
						int the_first_column = 0;
						cout << ">> ";
						cin >> the_first_column;
						cout << endl;

						cout <<"Введите индекс второго столбца: " << endl;
						int the_second_column = 0;
						cout << ">> ";
						cin >> the_second_column;
						cout << endl;

						if (matrix.swap_columns(the_first_column, the_second_column) == -1)
						{
							cout << "Неверные индексы!" << endl << endl;
						}
						else
						{
							cout << "Полученая матрица: " << endl;
							print_matrix(cout, matrix);	
						}
						break;
					}
				case '4':
					{
						cout << "Введите имя файла, хранящего вторую матрицу: " << endl;
						char filename_second[255] = "";
						cout << ">> ";
						cin >> filename_second;
						cout << endl;
						matrix_file.open(filename_second);

						if (! matrix_file.is_open())
						{
							cout << "Файл с матрицей невозможно открыть!" << endl << endl; 
						}
						else
						{
							int determinant_x = 0;
							int determinant_y = 0;

							matrix_file >> determinant_x >> determinant_y;
							matrix_file.close();

							Matrix matrix_second(determinant_x, determinant_y);
							load_matrix_from_file(filename_second, matrix_second);

							cout << "Исходная вторая матрица" << endl;
							print_matrix(cout, matrix_second);

							if (matrix_second.get_lock_matrix() == 0)
							{
								matrix = matrix * matrix_second;
								cout << "Полученая матрица: " << endl;
								print_matrix(cout, matrix);
							}
							else
							{
								cout << "Вторая матрица некорректна, операции невозможны!" << endl << endl;
							}
							matrix_second.~matrix_second();
						}
						break;
					}
				case '5':
					{
						cout << "Введите число: "<<endl;
						long double number = 1.0;
						cout << ">> ";
						cin >> number;
						cout << endl;

						matrix = matrix * number;
						cout << "Полученая матрица: " << endl;
						print_matrix(cout, matrix);
						break;
					}
				case '6':
					{
						cout << "Введите имя файла, хранящего вторую матрицу: "<<endl <<endl;
						char filename_second[255] = "";
						cout << ">> ";
						cin >> filename_second;
						cout << endl;
						matrix_file.open(filename_second);

						if (! matrix_file.is_open())
						{
							cout << "Файл с матрицей невозможно открыть!" << endl << endl; 
						}
						else
						{
							int determinant_x = 0;
							int determinant_y = 0;

							matrix_file >> determinant_x >> determinant_y;
							matrix_file.close();

							Matrix matrix_second(determinant_x, determinant_y);
							load_matrix_from_file(filename_second, matrix_second);

							cout << "Исходная вторая матрица" << endl;
							print_matrix(cout, matrix_second);

							if (matrix.get_dimension_x() == matrix_second.get_dimension_x() &
								matrix.get_dimension_y() == matrix_second.get_dimension_x())
							{
								matrix = matrix + matrix_second;
								cout << "Полученая матрица: " << endl;
								print_matrix(cout, matrix);
							}
							else
							{
								cout << "Матрицы не одинаковых размеров, вычисления невозможны!" << endl << endl; 
							}
							matrix_second.~matrix_second();
						}
						break;
					}
				case '7':
					{
						cout << "Введите имя файла, хранящего вторую матрицу: " << endl <<endl;
						char filename_second[255] = "";
						cout << ">> ";
						cin >> filename_second;
						cout << endl;
						matrix_file.open(filename_second);

						if (! matrix_file.is_open())
						{
							cout << "Файл с матрицей невозможно открыть!" << endl << endl; 
						}
						else
						{
							int determinant_x = 0;
							int determinant_y = 0;

							matrix_file >> determinant_x >> determinant_y;
							matrix_file.close();

							Matrix matrix_second(determinant_x, determinant_y);
							load_matrix_from_file(filename_second, matrix_second);

							cout << "Исходная вторая матрица" << endl;
							print_matrix(cout, matrix_second);

							if (matrix.get_dimension_x() == matrix_second.get_dimension_x() &
								matrix.get_dimension_y() == matrix_second.get_dimension_x())
							{
								matrix = matrix - matrix_second;
								cout << "Полученая матрица: " << endl;
								print_matrix(cout, matrix);
							}
							else
							{
								cout << "Матрицы не одинаковых размеров, вычисления невозможны!" << endl << endl; 
							}
							matrix_second.~matrix_second();
						}
						break;
					}
				case '8':
					{
						if (matrix.get_lock_determinant() == 0)
						{
							if (matrix.get_dimension_x() == 1)
							{
								cout << "Для матрицы порядка 1 обратной матрицы не существует!" << endl << endl;
							}
							else
							{
								if (matrix.count_determinant_matrix(1) != 0)
								{
									matrix = matrix.inverse_matrix();
									cout << "Полученая матрица: " << endl;
									print_matrix(cout, matrix);
								}
								else
								{
									cout << "Определитель матрицы равен нулю, обратной матрицы не существует!" << endl << endl;
								}
							}
						}
						else
						{
							cout << "Матрица не квадратного типа, обратной матрицы не существует!" << endl << endl;
						}
						break;
					}
				case '9':
					{
						matrix = matrix.transpose_matrix();

						cout << "Полученая матрица: " << endl;
						print_matrix(cout, matrix);
						break;
					}
				case '*':
					{
						if (matrix.get_lock_determinant() == 0)
						{
							cout << "След матрицы " << matrix.get_dimension_y() << "x" <<matrix.get_dimension_y()<< " равен " <<matrix.trace_matrix() << endl << endl;
						}
						else
						{
							cout << "Матрица не квадратного типа, вычислить след невозможно!" << endl << endl;
						}
						break;
					}
				case '&':
					{
						if (matrix.get_lock_matrix() == 0)
						{
							cout << "Ранг матрицы " << matrix.get_dimension_y() << "x" <<matrix.get_dimension_y()<< " равен " <<matrix.rank_matrix() << endl << endl;
						}
						else
						{
							cout << "Матрица некорректна, вычислить ранг невозможно!" << endl << endl;
						}
						break;
					}
				case '+':
					{
						char filename_save[255] = "C:\matrix_save.txt";
						cout << "Введите полный адрес создаваемого файла: " << endl;
						cout << ">> ";
						cin >> filename_save;
						fstream save_file(filename_save, 'w');
						matrix_file.open(filename_save);
						save_file << matrix.get_dimension_x() << "\r\n";
						save_file << matrix.get_dimension_y() << "\r\n";
						print_matrix(save_file, matrix);
						matrix_file.close();
						cout << "Текущая матрица сохранена в файле " << filename_save << endl << endl;
						break;
					}
				default:
					{
						cout << "Неверное действие!" << endl << endl;
						break;
					}
			}
			cout << "Вы хотите продолжить?(да - 1, нет - 0)" << endl;
			cout << ">> ";
			cin >> working;
			cout << endl;
			} while (working == '1');
		return 0;
	  } 
   }
}