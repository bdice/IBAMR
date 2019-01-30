// Filename LSLocateTrapezoidalInterface.h
// Written by Nishant Nangia

/////////////////////// INCLUDE GUARD ////////////////////////////////////

#ifndef included_LSLocateTrapezoidalInterface
#define included_LSLocateTrapezoidalInterface

///////////////////////////// INCLUDES ///////////////////////////////////
#include <ibamr/AdvDiffHierarchyIntegrator.h>
#include <ibtk/ibtk_utilities.h>
#include <tbox/Pointer.h>

namespace IBTK
{
class HierarchyMathOps;
}

/*
 * Pre processing call back function to be hooked into IBAMR:LInitStrategy
 */

void callLSLocateTrapezoidalInterfaceCallbackFunction(int D_idx,
                                                      SAMRAI::tbox::Pointer<IBTK::HierarchyMathOps> hier_math_ops,
                                                      double time,
                                                      bool initial_time,
                                                      void* ctx);

// Struct to maintain the properties of the trapezoidal interface
// Note that this class assumes the trapezoid will remain stationary
struct TrapezoidalInterface
{
    IBTK::Vector BL, BR, TL, TR;
};

class LSLocateTrapezoidalInterface
{
    /*!
     * \brief class LSLocateTrapezoidalInterface is a utility class which is used to identify
     * the trapezoidal interface for level set computations
     */
public:
    /*!
     * The only constructor of this class.
     */
    LSLocateTrapezoidalInterface(const std::string& object_name,
                                 SAMRAI::tbox::Pointer<IBAMR::AdvDiffHierarchyIntegrator> adv_diff_solver,
                                 SAMRAI::tbox::Pointer<SAMRAI::pdat::CellVariable<NDIM, double> > ls_var,
                                 TrapezoidalInterface* init_trapezoid);

    /*!
     * Destructor for this class.
     */
    ~LSLocateTrapezoidalInterface();

    /*!
     * Reinitialize the level set information
     */
    void setLevelSetPatchData(int D_idx,
                              SAMRAI::tbox::Pointer<IBTK::HierarchyMathOps> hier_math_ops,
                              const double time,
                              const bool initial_time);

    //////////////// PRIVATE /////////////////////////////

private:
    /*!
     * Default constructor is not implemented and should not be used.
     */
    LSLocateTrapezoidalInterface();

    /*!
     * Default assignment operator is not implemented and should not be used.
     */
    LSLocateTrapezoidalInterface& operator=(const LSLocateTrapezoidalInterface& that);

    /*!
     * Default copy constructor is not implemented and should not be used.
     */
    LSLocateTrapezoidalInterface(const LSLocateTrapezoidalInterface& from);

    /*!
     * Point to line distance
     */
    double pointToLineDistance(IBTK::Vector X0, IBTK::Vector P1, IBTK::Vector P2);

    /*!
     * Name of this object.
     */
    std::string d_object_name;

    /*!
     * Pointer to the advection-diffusion solver
     */
    SAMRAI::tbox::Pointer<IBAMR::AdvDiffHierarchyIntegrator> d_adv_diff_solver;

    /*!
     * Level set variable
     */
    SAMRAI::tbox::Pointer<SAMRAI::pdat::CellVariable<NDIM, double> > d_ls_var;

    /*!
     * Initial level set information.
     */
    TrapezoidalInterface* d_trapezoid;
};

#endif // #ifndef included_LSLocateTrapezoidalInterface