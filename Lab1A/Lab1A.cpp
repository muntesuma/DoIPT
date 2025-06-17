#include <iostream>
#include <memory>

using namespace std;

class IProductValidator {
public:
    virtual ~IProductValidator() = default;
    virtual bool IsValid(int price) const = 0;
};

class DefaultValidator : public IProductValidator {
public:
    bool IsValid(int price) const override {
        return price > 0;
    }
};

class CustomerServiceValidator : public IProductValidator {
public:
    bool IsValid(int price) const override {
        return price > 100000;
    }
};

class Product {
public:
    int price;

    void SetValidator(unique_ptr<IProductValidator> validator) {
        validator_ = move(validator);
    }

    bool IsValid() const {
        static DefaultValidator default_validator;
        return validator_ ? validator_->IsValid(price) : default_validator.IsValid(price);
    }

private:
    unique_ptr<IProductValidator> validator_;
};

int main() {
    Product p;
    cout << "p.price: " << p.price << endl;

    p.price = 0;
    cout << "Default (0): " << p.IsValid() << endl; // 0 (false)

    p.price = 500;
    cout << "Default (500): " << p.IsValid() << endl; // 1 (true)

    p.SetValidator(make_unique<CustomerServiceValidator>());
    cout << "CustomerService (500): " << p.IsValid() << endl; // 0 (false)

    p.price = 150000;
    cout << "CustomerService (150000): " << p.IsValid() << endl; // 1 (true)

    p.SetValidator(make_unique<DefaultValidator>());
    p.price = 0;
    cout << "DefaultValidator (0): " << p.IsValid() << endl; // 0 (false)

    p.price = 500;
    cout << "DefaultValidator (500): " << p.IsValid() << endl; // 1 (true)

    p.SetValidator(make_unique<CustomerServiceValidator>());
    p.SetValidator(nullptr);
    p.price = 0;
    cout << "Default (0): " << p.IsValid() << endl; // 0 (false)

    p.price = 500;
    cout << "Default (500): " << p.IsValid() << endl; // 1 (true)

    return 0;
}