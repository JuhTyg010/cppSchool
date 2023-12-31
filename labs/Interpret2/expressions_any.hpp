//
// Created by juhtyg on 31.12.23.
//

#ifndef DYNAMIC_POLYMORPHISM_EXPRESSIONS_ANY_H
#define DYNAMIC_POLYMORPHISM_EXPRESSIONS_ANY_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <any>
#include <utility>

namespace expressions {

    class Value {
    public:

         ~Value() noexcept = default; // `noexcept` is implicit in destructors
         Value() = default;
         Value(std::any value) : value_(std::move(value)) {}


         std::ostream& print(std::ostream& out){        //after 8 hours of debugging I found out that I had to used only int in printing
             if (value_.type() == typeid(int)) {
                 return out << std::any_cast<int>(value_);
             } else {
                 return out << std::any_cast<double>(value_);
             }
         }

         Value operator+(const Value& rhs) const {
             return rhs.add(value_);
         }

         std::any add(const std::any& rhs) const {
             if (value_.type() == typeid(int)) {
                 if (rhs.type() == typeid(int)) {
                     return std::any_cast<int>(value_) + std::any_cast<int>(rhs);
                 } else {
                     return static_cast<double>(std::any_cast<int>(value_)) + std::any_cast<double>(rhs);
                 }
             } else {
                 if (rhs.type() == typeid(int)) {
                     return std::any_cast<double>(value_) + static_cast<double>(std::any_cast<int>(rhs));
                 } else {
                     return std::any_cast<double>(value_) + std::any_cast<double>(rhs);
                 }
             }
         }
    private:
        std::any value_;
    };


    class Expression {
    public:
        using ptr = std::shared_ptr<Expression>;
        using const_ptr = std::shared_ptr<const Expression>;
        using context = std::unordered_map<std::string, Expression::ptr>;

        virtual Value evaluate(const context& ctx) const = 0;
        virtual ~Expression() noexcept = default; // `noexcept` is implicit in destructors
    };

    class Constant final : public Expression {
    public:
        explicit Constant(const Value& value) : value_(value) {}

        Value evaluate(const context&) const override {
            return value_;
        }

    private:
        Value value_;
    };

    class VariableExpression final : public Expression {
    public:
        explicit VariableExpression(std::string value) : value_(std::move(value)) {}

        Value evaluate(const context& ctx) const override {
            return ctx.at(value_)->evaluate(ctx); // throws `std::out_of_range` if the key is not found

        }

    private:
        std::string value_;
    };

    class AddExpression final : public Expression {
    public:
        AddExpression(Expression::ptr lhs, Expression::ptr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        Value evaluate(const context& ctx) const override {
            Value lhs = lhs_->evaluate(ctx);
            Value rhs = rhs_->evaluate(ctx);
            return  lhs + rhs;
        }

    private:
        Expression::ptr lhs_;
        Expression::ptr rhs_;
    };

} // namespace expressions


#endif //DYNAMIC_POLYMORPHISM_EXPRESSIONS_ANY_H
