#include <vector>
#include <memory>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

class Figure {
public:
	Figure(const string& _type) : type(_type) {}
	virtual string Type() const {
		return type;
	}
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
private:
	const string type;
	virtual void CalculatePerimeter() = 0;
	virtual void CalculateArea() = 0;
};

class Rectang : public Figure {
public:
	Rectang(const double& _a, const double& _b) : width(_a), height(_b), Figure("Rectangle") {
		CalculatePerimeter();
		CalculateArea();
	}

	double Perimeter() const override {
		return perimeter;
	}

	double Area() const override {
		return area;
	}

private:
	const double width, height;
	double perimeter, area;

	void CalculatePerimeter() override {
		perimeter = 2 * (width + height);
	}
	void CalculateArea() override {
		area = width * height;
	}

};

class Triang : public Figure {
public:
	Triang(const double& _a, const double& _b, const double& _c) : a(_a), b(_b), c(_c), Figure("Triangle") {
		CalculatePerimeter();
		CalculateArea();
	}

	double Perimeter() const override {
		return perimeter;
	}

	double Area() const override {
		return area;
	}

private:
	const double a, b, c;
	double perimeter, area;

	void CalculatePerimeter() override {
		perimeter = a + b + c;
	}
	void CalculateArea() override {
		double p = perimeter / 2;
		area = sqrt(p * (p - a) * (p - b) * (p - c));
	}
};

class Circle : public Figure {
public:
	Circle(const double& _r) : r(_r), Figure("Circle"){
		CalculatePerimeter();
		CalculateArea();
	}

	double Perimeter() const override {
		return perimeter;
	}

	double Area() const override {
		return area;
	}

private:
	const double r;
	double perimeter, area;

	void CalculatePerimeter() override {
		perimeter = 3.14 * r * 2;
	}
	void CalculateArea() override {
		area = 3.14 * r * r;
	}
};

shared_ptr<Figure> CreateFigure(stringstream& is)
{
	string figure;
	is >> figure;

	if (figure == "Triangle")
    {
		int a, b, c;
		is >> a >> b >> c;
		return make_shared<Triang>(a, b, c);
    }

	if (figure == "Rectangle")
	{
		int width, height;
		is >> width >> height;
		return make_shared<Rectang>(width, height);
	}

	int r;
	is >> r;
	return make_shared<Circle>(r);
}

int main() {
	vector<shared_ptr<Figure>> figures;
	stringstream is_1;
	is_1 << "Circle 3";
	figures.push_back(CreateFigure(is_1));
	stringstream is_2;
	is_2 << "Rectangle 40 13";
	figures.push_back(CreateFigure(is_2));
	for (const auto& current_figure : figures) {
				cout << fixed << setprecision(2)
				<< "Figure type: " << current_figure->Type() << ", "
				<< "perimeter = " << current_figure->Perimeter() << ", "
				<< "area = " << current_figure->Area() << endl;
	}

	return 0;
}
