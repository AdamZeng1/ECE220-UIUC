#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
string Shape::getName(){
  return name_;
}

Shape::Shape(string name){
  name_ = name;
}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
  width_ = width;
  length_ = length;
}
double Rectangle::getArea()const{
  return width_ * length_;
}
double Rectangle::getVolume()const{
  return 0;
}
Rectangle Rectangle::operator + (const Rectangle& rec){
  Rectangle c = Rectangle(0.0, 0.0);
  c.width_ = width_ + rec.width_;
  c.length_ = length_ + rec.length_;
  return c;
}
Rectangle Rectangle::operator - (const Rectangle& rec){
  Rectangle c = Rectangle(0.0, 0.0);
  c.width_ = max(0.0, width_ - rec.width_);
  c.length_ = max(0.0, length_ - rec.length_);
  return c;
}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle"){
  radius_ = radius;
}
double Circle::getArea()const{
  return radius_ * radius_ * M_PI;
}
double Circle::getVolume()const{
  return 0;
}
Circle Circle::operator + (const Circle& cir){
  Circle c = Circle(0.0);
  c.radius_ = radius_ + cir.radius_;
  return c;
}
Circle Circle::operator - (const Circle& cir){
  Circle c = Circle(0.0);
  c.radius_ = max(0.0, radius_ - cir.radius_);
  return c;
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere"){
  radius_ = radius;
}
double Sphere::getArea()const{
  return 4 * radius_ * radius_ * M_PI;
}
double Sphere::getVolume()const{
  return (4.0 / 3.0) * radius_ * radius_ * radius_ * M_PI;
}
Sphere Sphere::operator + (const Sphere& sph){
  Sphere c = Sphere(0.0);
  c.radius_ = radius_ + sph.radius_;
  return c;
}
Sphere Sphere::operator - (const Sphere& sph){
  Sphere c = Sphere(0.0);
  c.radius_ = max(0.0, radius_ - sph.radius_);
  return c;
}


double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
  width_ = width;
  length_ = length;
  height_ = height;
}
double RectPrism::getArea()const{
  return 2 * (length_ * width_ + length_ * height_ + width_ * height_);
}
double RectPrism::getVolume()const{
  return width_ * length_ * height_;
}
RectPrism RectPrism::operator + (const RectPrism& rectp){
  RectPrism c = RectPrism(0.0, 0.0, 0.0);
  c.width_ = width_ + rectp.width_;
  c.length_ = length_ + rectp.length_;
  c.height_ = height_ + rectp.height_;
  return c;
}
RectPrism RectPrism::operator - (const RectPrism& rectp){
  RectPrism c = RectPrism(0.0, 0.0, 0.0);
  c.width_ = max(0.0, width_ - rectp.width_);
  c.length_ = max(0.0, length_ - rectp.length_);
  c.height_ = max(0.0, height_ - rectp.height_);
  return c;
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
  int size, i;
  double num1, num2, num3;
  string name;
  vector<Shape *> v;
  ifstream ifs (file_name, std::ifstream::in);
  ifs >> size;
  for (i = 0; i < size; i++){
    Shape *obj;
    ifs >> name;
    if(name == "Rectangle"){
      ifs >> num1 >> num2;
      obj = new Rectangle(num1, num2);
    }
    else if(name == "Circle"){
      ifs >> num1;
      obj = new Circle(num1);
    }
    else if(name == "Sphere"){
      ifs >> num1;
      obj = new Sphere(num1);
    }
    else if(name == "RectPrism"){
      ifs >> num1 >> num2 >> num3;
      obj = new RectPrism(num1, num2, num3);
    }
    v.push_back(obj);
  }
	return v; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  int i;
  for(i = 0; i < shapes.size(); i++){
    if (max_area <= shapes[i]->getArea()){
      max_area = shapes[i]->getArea();
    }
  }
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  int i;
  for(i = 0; i < shapes.size(); i++){
    if (max_volume <= shapes[i]->getVolume()){
      max_volume = shapes[i]->getVolume();
    }
  }

	return max_volume;
}
