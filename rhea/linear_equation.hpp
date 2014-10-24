//---------------------------------------------------------------------------
/// \file   linear_equation.hpp
/// \brief  A linear equation constraint
//
// This file is part of Rhea.  Rhea is free software: you can redistribute
// it and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version 3
// of the License, or (at your option) any later version.
//
// Rhea is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Rhea.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2014, nocte@hippie.nu
//---------------------------------------------------------------------------
#pragma once

#include "linear_constraint.hpp"
#include "linear_expression.hpp"

namespace rhea
{

/** A constraint of the form \f$expr = 0\f$. */
class linear_equation : public linear_constraint
{
public:
    /** Create a new constraint of the form \f$e = 0\f$.
     * \param e     The expression
     * \param s     The constraint's strength
     * \param weight The constraint's weight */
    linear_equation(linear_expression e = linear_expression(0.0),
                    const strength& s = strength::required(),
                    double weight = 1.0)
        : linear_constraint{std::move(e), s, weight}
    {
    }

    /** Create a new constraint of the form \f$e = v\f$, or rather
     ** \f$e - v = 0\f$.
     * \param v     The variable
     * \param e     The expression
     * \param s     The constraint's strength
     * \param weight The constraint's weight */
    linear_equation(const variable& v, linear_expression e,
                    const strength& s = strength::required(),
                    double weight = 1.0)
        : linear_constraint{std::move(e), s, weight}
    {
        expr_.set(v, -1);
    }

    /** Create a new constraint of the form \f$e = v\f$, or rather
     ** \f$e - v = 0\f$.
     * \param v     The variable
     * \param e     The expression
     * \param s     The constraint's strength
     * \param weight The constraint's weight */
    linear_equation(linear_expression e, const variable& v,
                    const strength& s = strength::required(),
                    double weight = 1.0)
        : linear_constraint{std::move(e), s, weight}
    {
        expr_.set(v, -1);
    }

    /** Create a new constraint of the form \f$e_a = e_b\f$, or rather
     ** \f$e_a - e_b = 0\f$.
     * \param lhs   The expression \f$e_a\f$
     * \param rhs   The expression \f$e_b\f$
     * \param s     The constraint's strength
     * \param weight The constraint's weight */
    linear_equation(linear_expression lhs, const linear_expression& rhs,
                    strength s = strength::required(), double weight = 1.0)
        : linear_constraint{std::move(lhs), s, weight}
    {
        expr_ -= rhs;
    }

    virtual ~linear_equation() {}

    virtual bool is_satisfied() const { return expr_.evaluate() == 0.0; }
};

//--------------------------------------------------------------------------

inline linear_equation operator==(linear_expression lhs, const variable& rhs)
{
    return lhs -= rhs;
}

inline linear_equation operator==(linear_expression lhs,
                                  const linear_expression& rhs)
{
    return lhs -= rhs;
}

inline linear_equation operator==(const variable& lhs,
                                  const linear_expression& rhs)
{
    return rhs - lhs;
}

inline linear_equation operator==(const variable& lhs, const variable& rhs)
{
    return linear_expression{lhs} -= rhs;
}

inline linear_equation operator==(const variable& lhs, double rhs)
{
    return linear_expression{lhs, 1, -rhs};
}

} // namespace rhea
