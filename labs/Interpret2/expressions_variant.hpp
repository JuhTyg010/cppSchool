#ifndef EXPRESSIONS1_HPP
#define EXPRESSIONS1_HPP

#include <iostream>
#include <memory>
#include <cassert>
#include <unordered_map>
#include <variant>

namespace expressions {

// an abstract base class for all values
// - the fact that it is abstract is deduced from the `= 0` in the declaration of `print` (see below)
// this is equivalent to an interface in Java or C# (as long as we don't add any data members)
    class Value {
    public:


         ~Value() noexcept = default; // `noexcept` is implicit in destructors

         Value(std::variant<int,double> value) : value_(value) {}
         std::ostream& print(std::ostream& out){
                if (std::holds_alternative<int>(value_))
                    return out << std::get<int>(value_);
                else
                    return out << std::get<double>(value_);
         }

          Value operator+(const Value& rhs) const {
             return rhs.add(value_);
         }
         std::variant<int,double> add(std::variant<int,double> rhs) const {
                if (std::holds_alternative<int>(value_)) {
                    if (std::holds_alternative<int>(rhs))
                        return std::get<int>(value_) + std::get<int>(rhs);
                    else
                        return static_cast<double >(std::get<int>(value_)) + std::get<double>(rhs);
                } else {
                    if (std::holds_alternative<int>(rhs))
                        return std::get<double>(value_) + static_cast<double>(std::get<int>(rhs));
                    else
                        return std::get<double>(value_) + std::get<double>(rhs);
                }
         }
    private:
        std::variant<int, double> value_;
    };

// use `final` if you don't want to allow further inheritance (use sparingly, here it is mainly for demonstration purposes)


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
        explicit Constant(Value value) : value_(std::move(value)) {}

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


            return lhs + rhs;

        }

    private:
        Expression::ptr lhs_;
        Expression::ptr rhs_;
    };

} // namespace expressions
#endif // EXPRESSIONS1_HPP
