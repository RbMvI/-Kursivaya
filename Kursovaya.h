#ifndef KURSOVAYA_H
#define KURSOVAYA_H
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

bool is_mty(ifstream& pFile) {
	return pFile.peek() == std::ifstream::traits_type::eof();
}
bool is_fnd(string A, string B) {
	auto l = A.find(B);
	return l <= A.size();
}

class Product
{
	friend class ProductService;
	string name;
	string prodcode;
	string Quantity;
	int num;

public:
	string getname()
	{
		return name;
	}
	string getProdcode()
	{
		return prodcode;
	}
	string getQuantity()
	{
		return Quantity;
	}
	int getNum() {
		return num;
	}
	friend ostream& operator<<(ostream& os, Product const& Product);
	friend istream& operator>>(istream& is, Product& Product);
protected:
	void setname(string Name = "default name")
	{
		name = Name;
	}
	void setProdcode(string Prodcode)
	{
		prodcode = Prodcode;
	}
	void setQuantity(string Quantity)
	{
		Quantity = Quantity;
	}
	void setNum(int num)
	{
		this->num = num;
	}
};
ostream& operator<<(ostream& os, Product const& Product)
{
	os << Product.num << " " << Product.name << " " << Product.prodcode << " " << Product.Quantity << " ";
	return os;
}
istream& operator>>(istream& is, Product& Product)
{
	is >> Product.name >> Product.prodcode >> Product.Quantity;
	return is;
}
class ProductService : Product
{
	vector <Product> ProductList;	//FILE List = "List.txt";

	struct cmpname {
		bool operator()(Product A, Product B) const { return A.getname() < B.getname(); }
	}cmpname;

public:
	void DeleteProduct(int num)
	{
		if (num <= ProductList.size())  ProductList.erase(ProductList.begin() + num - 1);
		else cout << "There is no product with that number" << endl;
	}
	vector<Product> FindProduct(string sp)
	{
		vector<Product> fnd;
		for (int i = 0; i < ProductList.size(); i++) {
			if (is_fnd(ProductList[i].getname(), sp) || is_fnd(ProductList[i].getProdcode(), sp) || is_fnd(to_string(ProductList[i].getNum()), sp) || is_fnd(ProductList[i].getQuantity(), sp))
			{
				fnd.push_back(ProductList[i]);
			}
		}
		return fnd;
	}
	vector <Product> SortLike(int opt)
	{
		vector<Product> Product = ProductList;
		switch (opt) {
		
		case 1:
		{
			sort(Product.begin(), Product.end(), cmpname);
			break;
		}
		}
		return Product;
	}
	void CreateNewProduct(string name, string Prodcode, string Quantity)
	{
		Product P;
		P.setname(name);
		P.setProdcode(Prodcode);
		P.setQuantity(Quantity);
		P.setNum(ProductList.size() + 1);
		ProductList.push_back(P);
	}
	void SaveProductList()
	{
		remove("List.txt");
		ofstream fout;
		fout.open("List.txt");
		fout << ProductList.size() << endl;
		for (int i = 0; i < ProductList.size(); i++) {
			fout << ProductList[i] << endl;
		}
		fout.close();
	}
	void LoadBase()
	{
		ifstream fin;
		fin.open("List.txt");
		if (!fin.is_open())
		{
			cout << "File is no opened" << endl;
			return;
		}


		if (is_mty(fin))
		{
			cout << "Fill the file first" << endl;
			return;
		}
		else cout << "Base was loaded" << endl;
		int n;
		fin >> n;
		ProductList.erase(ProductList.begin(), ProductList.end());
		for (int i = 0; i < n; i++)
		{
			Product A;
			fin >> A;
			this->CreateNewProduct(A.getname(), A.getProdcode(), A.getQuantity());
		}
		fin.close();
	}
};

#endif
