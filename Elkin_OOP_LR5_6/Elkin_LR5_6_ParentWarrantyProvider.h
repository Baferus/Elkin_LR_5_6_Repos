#pragma once

class WarrantyProvider {
public:
    virtual void extendWarranty(int months) = 0;
    virtual int getWarrantyMonths() const = 0;
    virtual ~WarrantyProvider() = default;
};