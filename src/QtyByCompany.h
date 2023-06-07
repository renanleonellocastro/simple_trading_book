#include <iostream>

class QtyByCompany {
public:
    std::string company;
    unsigned int quantity;

    QtyByCompany(const std::string& company, unsigned int quantity) : company(company), quantity(quantity)
    {
    }

    bool operator<(const QtyByCompany& other) const
    {
        return quantity < other.quantity;
    }
};
