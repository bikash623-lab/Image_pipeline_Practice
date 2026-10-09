#include <iostream>

// int main(){
//     int a = 5;
//     int* ptr = &a;
   
//     *ptr = 20;
//     std::cout << ptr << std::endl;
//     std::cout << &a << std::endl;
//     ptr++;
//     std::cout << *ptr << std::endl;
//     std::cout << ptr << std::endl;
//     return 0;
// }


// int main(){
//     size_t a = 5; //same like int but large byte size mean can hold larger value
//     std::cout << sizeof(a) << std::endl;


//     unsigned char images[] = {1,2,3,4,5,6};
//     std::cout << sizeof(images)/sizeof(images[0]) << std::endl;
//     std::cout << static_cast<int> (images[1]) << std::endl;
//     return 0;
// }


// #include <iostream>
// #include <string>


// class ParentA{
// public:
//     std::string name;
//     double age;

//     ParentA(std::string name, double age) : name(std::move(name)), age(age){
//         std::cout <<"ParentA Constructor." << std::endl;
//     }

//     void showA() const{
//         std::cout << "Name from ParentA:  "<< name << std::endl;
//     }
// };

// class ParentB{
// public:
//     int id;
//     ParentB(int id) : id(id){
//         std::cout <<"ParentB Constructot" << std::endl;
//     }

//     void showB() const{
//         std::cout << "ID from ParentB:" << id << std::endl;
//     }
// };

// class Child : public ParentA, public ParentB{
// public:
//     double gpa;
//     Child(std::string name, int id, double gpa) : ParentA(std::move(name)), ParentB(id), gpa(gpa){
//         std:: cout <<"Child Constructor." << std::endl;
//     }

//     void showAll() const{
//         showA();
//         showB();
//         std::cout <<"GPA:" << gpa << std::endl;
//     }
// };


// int main(){
//     Child c("Bikash", 101, 3.9);
//     std::cout << "__" << std::endl;
//     c.showAll();
//     return 


// #include <iostream>
// #include <string>
// #include <utility>

// class Person{
// public:
//     std::string name;
//     Person(std::string name) : name(std::move(name)){}
//     virtual ~Person(){
//         std::cout << "Person Destructor." << std::endl;
//     }

//     virtual void display() const{
//         std::cout << "Name:" << name << std::endl;
//     }
// };

// class Student : public Person{
// public:
//     double* gradePtr;

//     Student(std::string name, double grade): Person(std::move(name)), gradePtr(new double(grade)){
//         std::cout << "Student Constructor." << std::endl;
//     }

//     Student(const Student &obj) : Person(obj), gradePtr(new double(*obj.gradePtr)){
//         std::cout << "Student Copy COnstructor." << std::endl;
//     }

//     ~Student(){
//         delete gradePtr;
//         std::cout << "Student Destructor" << std::endl;
//     }

//     void display() const override {
//         std::cout << "Name:" << name << "\n" << "Grade:" << *gradePtr << std::endl;
//     }
// };

// int main(){
//     Person P1("Bikash");
//     P1.display();
    
//     std::cout << "---" << std::endl;
    
//     Student S1("Pratikshya", 4.0);
//     S1.display();
    
//     std::cout << "---" << std::endl;
    
//     // Testing deep copy with inheritance
//     Student S2(S1);
//     S2.display();
    
//     std::cout << "---" << std::endl;
//     return 0;
// }


#include <iostream>
#include <string>

class Person{
private:
    int age;
public:
    Person(int age2) : age(age2){}

    void display() const{
        std:: cout << age << std::endl;
    }
    
};  

int main(){
    Person P1(25);
    P1.display();

    return 0;

}