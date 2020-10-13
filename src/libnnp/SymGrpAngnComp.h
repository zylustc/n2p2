// n2p2 - A neural network potential package
// Copyright (C) 2018 Andreas Singraber (University of Vienna)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef SYMGRPANGNCOMP_H
#define SYMGRPANGNCOMP_H

#include "SymGrpBaseComp.h"
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace nnp
{

struct Atom;
class ElementMap;
class SymFnc;
class SymFncAngnComp;

//TODO /** Angular symmetry function group (type 3)
//TODO  *
//TODO  * @f[
//TODO    G^9_i = 2^{1-\zeta} \sum_{\substack{j,k\neq i \\ j < k}}
//TODO            \left( 1 + \lambda \cos \theta_{ijk} \right)^\zeta
//TODO            \mathrm{e}^{-\eta( (r_{ij}-r_s)^2 + (r_{ik}-r_s)^2 ) }
//TODO            f_c(r_{ij}) f_c(r_{ik}) 
//TODO  * @f]
//TODO  * Common features:
//TODO  * - element of central atom
//TODO  * - element of neighbor atom 1
//TODO  * - element of neighbor atom 2
//TODO  * - cutoff type
//TODO  * - @f$r_c@f$
//TODO  * - @f$\alpha@f$
//TODO  */
class SymGrpAngnComp : public SymGrpBaseComp
{
public:
    /** Constructor, sets type = 21
     */
    SymGrpAngnComp(ElementMap const& elementMap);
    /** Overload == operator.
     */
    virtual bool operator==(SymGrp const& rhs) const;
    /** Overload < operator.
     */
    virtual bool operator<(SymGrp const& rhs) const;
    /** Potentially add a member to group.
     *
     * @param[in] symmetryFunction Candidate symmetry function.
     * @return If addition was successful.
     *
     * If symmetry function is compatible with common feature list its pointer
     * will be added to #members.
     */
    virtual bool addMember(SymFnc const* const symmetryFunction);
    /** Sort member symmetry functions.
     *
     * Also allocate and precalculate additional stuff.
     */
    virtual void sortMembers();
    /** Fill #scalingFactors with values from member symmetry functions.
     */
    virtual void setScalingFactors();
    /** Calculate all symmetry functions of this group for one atom.
     *
     * @param[in,out] atom Atom for which symmetry functions are caluclated.
     * @param[in] derivatives If also symmetry function derivatives will be
     *                        calculated and saved.
     */
    virtual void calculate(Atom& atom, bool const derivatives) const;
    /** Give symmetry function group parameters on multiple lines.
     *
     * @return Vector of string containing symmetry function parameters lines.
     */
    virtual std::vector<std::string>
                 parameterLines() const;

private:
    /// Element index of neighbor atom 1 (common feature).
    std::size_t                        e1;
    /// Element index of neighbor atom 2 (common feature).
    std::size_t                        e2;
    /// Vector of all group member pointers.
    std::vector<SymFncAngnComp const*> members;
};

}

#endif
