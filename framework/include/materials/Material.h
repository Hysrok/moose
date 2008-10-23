#include "Kernel.h"

#ifndef MATERIAL_H
#define MATERIAL_H

/**
 * Holds material properties that are assigned to blocks.
 */
class Material : public Kernel
{
public:

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  Material(std::string name,
           Parameters parameters,
           unsigned int block_id,
           std::vector<std::string> coupled_to,
           std::vector<std::string> coupled_as)
    :Kernel(name, parameters, Kernel::_es->get_system(0).variable_name(0), false, coupled_to, coupled_as),
    _zero(0),
    _grad_zero(0),
    _block_id(block_id),
    _has_temp(isCoupled("temp")),
    _temp(_has_temp ? coupledVal("temp") : _zero),
    _grad_temp(_has_temp ? coupledGrad("temp") : _grad_zero),
    _has_oxygen(isCoupled("oxygen")),
    _oxygen(_has_oxygen ? coupledVal("oxygen") : _zero),
    _grad_oxygen(_has_oxygen ? coupledGrad("oxygen") : _grad_zero),
    _has_neut(isCoupled("neut")),
    _neut(_has_neut ? coupledVal("neut") : _zero),
    _has_pre(isCoupled("pre")),
    _pre(_has_pre ? coupledVal("pre") : _zero),
    _grad_pre(_has_pre ? coupledGrad("pre") : _grad_zero),
    _has_xmom(isCoupled("xmom")),
    _xmom(_has_xmom ? coupledVal("xmom") : _zero),
    _has_ymom(isCoupled("ymom")),
    _ymom(_has_ymom ? coupledVal("ymom") : _zero),
    _has_zmom(isCoupled("zmom")),
    _zmom(_has_zmom ? coupledVal("zmom") : _zero),
    _has_rmom(isCoupled("rmom")),
    _rmom(_has_rmom ? coupledVal("rmom") : _zero),
    _has_thetamom(isCoupled("thetamom")),
    _thetamom(_has_thetamom ? coupledVal("thetamom") : _zero),    
    _has_fluid_temp(isCoupled("fluid_temp")),
    _fluid_temp(_has_fluid_temp ? coupledVal("fluid_temp") : _zero),
    _has_solid_temp(isCoupled("solid_temp")),
    _solid_temp(_has_solid_temp ? coupledVal("solid_temp") : _zero),
    _thermal_conductivity(1),
    _thermal_conductivity_fluid(1),
    _thermal_conductivity_solid(1),
    _thermal_expansion(1),
    _specific_heat(1),
    _specific_heat_fluid(1),
    _specific_heat_solid(1),
    _density(1),
    _youngs_modulus(1),
    _poissons_ratio(1),
    _neutron_diffusion_coefficient(1),
    _neutron_absorption_xs(1),
    _neutron_fission_xs(1),
    _neutron_per_fission(1),
    _neutron_velocity(1),
    _neutron_per_power(1),
    _heat_xfer_coefficient(1),
    _gas_constant(1),
    _porosity(1)
  {}

  virtual ~Material(){}

  /** 
   * Block ID the Material is active on.
   * 
   * @return The block ID.
   */
  unsigned int blockID(){ return _block_id; }

  /**
   * Causes the material to recompute all of it's values
   * at the quadrature points.  This is a helper in the base
   * class that does a bunch of common setup first then calls
   * computeProperties().
   */
  void materialReinit();

  std::vector<Real> & thermalConductivity(){ return _thermal_conductivity; }
  std::vector<Real> & thermalConductivityFluid(){ return _thermal_conductivity_fluid; }
  std::vector<Real> & thermalConductivitySolid(){ return _thermal_conductivity_solid; }
  std::vector<Real> & thermalExpansion(){ return _thermal_expansion; }
  std::vector<Real> & specificHeat(){ return _specific_heat; }
  std::vector<Real> & specificHeatFluid(){ return _specific_heat_fluid; }
  std::vector<Real> & specificHeatSolid(){ return _specific_heat_solid; }
  std::vector<Real> & density(){ return _density; }
  
  std::vector<Real> & youngsModulus(){ return _youngs_modulus; }
  std::vector<Real> & poissonsRatio(){ return _poissons_ratio; }

  std::vector<Real> & neutronDiffusionCoefficient(){ return _neutron_diffusion_coefficient; }
  std::vector<Real> & neutronAbsorptionXS(){ return _neutron_absorption_xs; }
  std::vector<Real> & neutronFissionXS(){ return _neutron_fission_xs; }
  std::vector<Real> & neutronPerFission(){ return _neutron_per_fission; }
  std::vector<Real> & neutronVelocity(){ return _neutron_velocity; }
  std::vector<Real> & neutronPerPower(){ return _neutron_per_power; }

  std::vector<Real> & heatXferCoefficient(){ return _heat_xfer_coefficient; }

  std::vector<Real> & fluidResistanceCoefficient(){return _fluid_resistance_coefficient;}
  std::vector<Real> & gasConstant(){return _gas_constant;}
  std::vector<Real> & porosity(){return _porosity;}

private:
  std::vector<Real> _zero;
  std::vector<RealGradient> _grad_zero;

protected:

  /**
   * All materials must override this virtual.
   * This is where they fill up the vectors with values.
   */
  virtual void computeProperties() = 0;

  /**
   * Block ID this material is active on.
   */
  unsigned int _block_id;

  /**
   * Doesn't do anything for materials.
   */
  virtual Real computeQpResidual(){ return 0; }

  bool _has_temp;
  std::vector<Real> & _temp;
  std::vector<RealGradient> & _grad_temp;

  bool _has_oxygen;  
  std::vector<Real> & _oxygen;
  std::vector<RealGradient> & _grad_oxygen;

  bool _has_neut;
  std::vector<Real> & _neut;

  bool _has_pre;
  std::vector<Real> & _pre;
  std::vector<RealGradient> & _grad_pre;
  
  bool _has_xmom;
  std::vector<Real> & _xmom;
  bool _has_ymom;
  std::vector<Real> & _ymom;
  bool _has_zmom;
  std::vector<Real> & _zmom;
  bool _has_rmom;
  std::vector<Real> & _rmom;
  bool _has_thetamom;
  std::vector<Real> & _thetamom;

  
  bool _has_fluid_temp;
  std::vector<Real> & _fluid_temp;
  
  bool _has_solid_temp;
  std::vector<Real> & _solid_temp;
  
  std::vector<Real> _thermal_conductivity;
  std::vector<Real> _thermal_conductivity_fluid;
  std::vector<Real> _thermal_conductivity_solid;
  std::vector<Real> _thermal_expansion;
  std::vector<Real> _specific_heat;
  std::vector<Real> _specific_heat_fluid;
  std::vector<Real> _specific_heat_solid;
  std::vector<Real> _density;
  std::vector<Real> _youngs_modulus;
  std::vector<Real> _poissons_ratio;
  std::vector<Real> _neutron_diffusion_coefficient;
  std::vector<Real> _neutron_absorption_xs;
  std::vector<Real> _neutron_fission_xs;
  std::vector<Real> _neutron_per_fission;
  std::vector<Real> _neutron_velocity;
  std::vector<Real> _neutron_per_power;
  std::vector<Real> _heat_xfer_coefficient;
  std::vector<Real> _fluid_resistance_coefficient;
  std::vector<Real> _gas_constant;
  std::vector<Real> _porosity;
};

#endif //MATERIAL_H
