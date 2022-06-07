#include "Kursovaya.h"
int main()
{
	setlocale(LC_ALL, "Russian");
	ProductService pr;
	int Strock = 4;

	int nomer;
	while (true)
	{
		cout << "1 - Greate new Product" << endl << endl
			<< "2 - Find Product" << endl << endl
			<< "3 - Delete Product" << endl << endl
			<< "4 - Sort all Products" << endl << endl
			<< "5 - Save base of Products" << endl << endl
			<< "6 - Load base of Products" << endl << endl;

		cin >> nomer; 
		switch (nomer)
		{

		case 1: // Greate new Product
		{
			cout << "Write down Information about the Product (Name, Code and Quantity) : " << endl;
			vector<string> anw(Strock);
			for (int i = 0; i < Strock; i++)
			{
				cin >> anw[i];
			}
			pr.CreateNewProduct(anw[0], anw[1], anw[2]);
			
			break;
		}

		case 2: // Find Product
		{
			cout << "Enter Product's Information: Name or Code or Quantity of Products or Arrival date" << endl;
			string info;
			cin >> info;
			vector<Product> Fn = pr.FindProduct(info);
			int infosize = Fn.size();
			if (infosize == 0)
			{
				cout << "There is no such Product" << endl;
			}
			else {
				cout << "Product was found " << infosize << "   " << "Check information out:" << endl;
				for (int i = 0; i < Fn.size(); i++) {
					cout << Fn[i] << endl;
				}
			}
			break;
		}

		case 3: // Delete Product
		{
			cout << "Enter number of Product you want to delete" << endl;
			int delpr;
			cin >> delpr;
			pr.DeleteProduct(delpr);
			break;
		}

		case 4: // Sort all Products
		{
			int number=1;
			vector<Product> A = pr.SortLike(number);
			for (int i = 0; i < A.size(); i++)
			{
				cout << A[i] << endl;
			}
			break;
		}

		case 5: // Save base of Products
		{
			pr.SaveProductList();
		}

		case 6: // Load base of Products
		{
			pr.LoadBase();

			break;
		}
		}
	}
	return 0;
}