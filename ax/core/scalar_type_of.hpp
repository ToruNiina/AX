#ifndef AX_SCALAR_TYPE_OF
#define AX_SCALAR_TYPE_OF

namespace ax
{

template<typename matrixT>
struct scalar_type_of
{
    typedef typename matrixT::scalar_type type;
};

} // ax

#endif /* AX_SCALAR_TYPE_OF */
