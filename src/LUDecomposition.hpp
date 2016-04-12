#ifndef AX_LU_DECOMPOSE_H
#define AX_LU_DECOMPOSE_H
#include "Matrix.hpp"
#include "DynamicMatrix.hpp"

namespace ax
{

template<class M>
class Doolittle;

// template<class M>
// class Crout;
//
// template<class M>
// class Cholesky;

template<class M, class Solver = Doolittle<M>>
class StaticLUDecomposer
{
  public:
    StaticLUDecomposer(const M& mat)
        : mat_(mat)
    {}
    ~StaticLUDecomposer() = default;

    void  solve(){Solver::solve(mat_, L_, U_);}

    const RealMatrix<M::row, M::col> get_L() const {return L_;}
    const RealMatrix<M::row, M::col> get_U() const {return U_;}

  private:

    const M& mat_;

    RealMatrix<M::row, M::col> L_;
    RealMatrix<M::row, M::col> U_;
};

template<class M>
class Doolittle
{
  public:
    static void solve(const M& mat,
                      RealMatrix<M::row, M::col>& L,
                      RealMatrix<M::row, M::col>& U);

  private:
    static void rec_solve(const std::size_t step, 
                          RealMatrix<M::row, M::col>& LU);
};

template<class M>
void Doolittle<M>::solve(const M& mat,
                         RealMatrix<M::row, M::col>& L,
                         RealMatrix<M::row, M::col>& U)
{
    RealMatrix<M::row, M::col> LU = mat;
    // TODO: exchange if 0 devide occurs

    Doolittle<M>::rec_solve(0, LU);

    // ~~~~~~~ store values in L and U ~~~~~~~
    for(std::size_t i=0; i < M::row; ++i)
    {
        L(i, i) = 1e0;
        for(std::size_t j = 0; j < i; ++j)
            L(i, j) = LU(i, j);

        for(std::size_t j = i+1; j < M::col; ++j)
            L(i, j) = 0e0;
    }
    for(std::size_t i=0; i < M::row; ++i)
    {
        for(std::size_t j = 0; j < i; ++j)
            U(i, j) = 0e0;

        for(std::size_t j = i; j < M::col; ++j)
            U(i, j) = LU(i, j);
    }
    return;
}

template<class M>
void Doolittle<M>::rec_solve(const std::size_t step,
                             RealMatrix<M::row, M::col>& LU)
{
    if(step >= M::row - 1)
        return;
    else
    {
        const double inv_nn = 1e0 / LU(step,step);
        for(std::size_t i = step+1; i<M::row; ++i)
            LU(i,step) = LU(i,step) * inv_nn;

        for(std::size_t i = step+1; i<M::row; ++i)
            for(std::size_t j = step+1; j<M::col; ++j)
            {
                LU(i,j) = LU(i,j) - (LU(step,j) * LU(i,step));
            }
        return rec_solve(step + 1, LU);
    }
}

// ~~~~~~~~~~~~~~~~~~ Dynamic Size Matrix ~~~~~~~~~~~~~~~~~~~~
class DynamicDoolittle;

template<class Solver = DynamicDoolittle>
class DynamicLUDecomposer
{
  public:
    DynamicLUDecomposer(const RealDynamicMatrix& mat)
        : mat_(mat)
    {}
    ~DynamicLUDecomposer() = default;

    void  solve(){Solver::solve(mat_, L_, U_);}

    const RealDynamicMatrix get_L() const {return L_;}
    const RealDynamicMatrix get_U() const {return U_;}

  private:

    const RealDynamicMatrix& mat_;

    RealDynamicMatrix L_;
    RealDynamicMatrix U_;
};

class DynamicDoolittle
{
  public:
    static void solve(const RealDynamicMatrix& mat,
                            RealDynamicMatrix& L,
                            RealDynamicMatrix& U);

  private:
    static void rec_solve(const std::size_t step, 
                          RealDynamicMatrix& LU);
};

void DynamicDoolittle::solve(const RealDynamicMatrix& mat,
                                   RealDynamicMatrix& L,
                                   RealDynamicMatrix& U)
{
    RealDynamicMatrix LU = mat;
    // TODO: exchange if 0 devide occurs

    DynamicDoolittle::rec_solve(0, LU);

    // ~~~~~~~ store values in L and U ~~~~~~~
    for(std::size_t i=0; i < mat.size_row(); ++i)
    {
        L(i, i) = 1e0;
        for(std::size_t j = 0; j < i; ++j)
            L(i, j) = LU(i, j);

        for(std::size_t j = i+1; j < mat.size_col(); ++j)
            L(i, j) = 0e0;
    }
    for(std::size_t i=0; i < mat.size_row(); ++i)
    {
        for(std::size_t j = 0; j < i; ++j)
            U(i, j) = 0e0;

        for(std::size_t j = i; j < mat.size_col(); ++j)
            U(i, j) = LU(i, j);
    }
    return;
}

void DynamicDoolittle::rec_solve(const std::size_t step,
                                 RealDynamicMatrix& LU)
{
    if(step >= LU.size_row() - 1)
        return;
    else
    {
        const double inv_nn = 1e0 / LU(step,step);
        for(std::size_t i = step+1; i<LU.size_row(); ++i)
            LU(i,step) = LU(i,step) * inv_nn;

        for(std::size_t i = step+1; i<LU.size_row(); ++i)
            for(std::size_t j = step+1; j<LU.size_col(); ++j)
            {
                LU(i,j) = LU(i,j) - (LU(step,j) * LU(i,step));
            }
        return rec_solve(step + 1, LU);
    }
}

}
#endif /* AX_LU_DECOMPOSE_H */
