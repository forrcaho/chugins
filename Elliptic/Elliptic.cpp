//-----------------------------------------------------------------------------
// Entaro ChucK Developer!
// This is a Chugin boilerplate, generated by chugerate!
//-----------------------------------------------------------------------------

// this should align with the correct versions of these ChucK files
#include "chuck_dl.h"
#include "chuck_def.h"
#include "elldefs.h"

// general includes
#include <stdio.h>
#include <limits.h>

// declaration of chugin constructor
CK_DLL_CTOR(elliptic_ctor);
// declaration of chugin desctructor
CK_DLL_DTOR(elliptic_dtor);

// example of getter/setter
CK_DLL_MFUN(elliptic_setParam);
CK_DLL_MFUN(elliptic_getParam);

// for Chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICK(elliptic_tick);

// this is a special offset reserved for Chugin internal data
t_CKINT elliptic_data_offset = 0;

extern "C" {
  extern double ellset(double f1, double f2, double f3,
		       double ripple, double atten, double srate);
  extern int get_nsections(void);
  extern int ellpset(EllSect [], float *);
  
  extern float ellipse(float, int, EllSect [], float);
}

// class definition for internal Chugin data
// (note: this isn't strictly necessary, but serves as example
// of one recommended approach)
class Elliptic
{
public:
  // constructor
  Elliptic( t_CKFLOAT fs)
  {
    m_param = 0;
  }
  
  // for Chugins extending UGen
  SAMPLE tick( SAMPLE in )
  {
    // default: this passes whatever input is patched into Chugin
    return in;
  }
  
  // set parameter example
  float setParam( t_CKFLOAT p )
  {
    m_param = p;
    return p;
  }
  
  // get parameter example
  float getParam() { return m_param; }
  
private:
  // instance data
  float m_param;
  
};


// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( Elliptic )
{
  // hmm, don't change this...
  QUERY->setname(QUERY, "Elliptic");
  
  // begin the class definition
  // can change the second argument to extend a different ChucK class
  QUERY->begin_class(QUERY, "Elliptic", "UGen");
  
  // register the constructor (probably no need to change)
  QUERY->add_ctor(QUERY, elliptic_ctor);
  // register the destructor (probably no need to change)
  QUERY->add_dtor(QUERY, elliptic_dtor);
  
  // for UGen's only: add tick function
  QUERY->add_ugen_func(QUERY, elliptic_tick, NULL, 1, 1);
  
  // NOTE: if this is to be a UGen with more than 1 channel, 
  // e.g., a multichannel UGen -- will need to use add_ugen_funcf()
  // and declare a tickf function using CK_DLL_TICKF
  
  // example of adding setter method
  QUERY->add_mfun(QUERY, elliptic_setParam, "float", "param");
  // example of adding argument to the above method
  QUERY->add_arg(QUERY, "float", "arg");
  
  // example of adding getter method
  QUERY->add_mfun(QUERY, elliptic_getParam, "float", "param");
  
  // this reserves a variable in the ChucK internal class to store 
  // referene to the c++ class we defined above
  elliptic_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
  
  // end the class definition
  // IMPORTANT: this MUST be called!
  QUERY->end_class(QUERY);
  
  // wasn't that a breeze?
  return TRUE;
}


// implementation for the constructor
CK_DLL_CTOR(elliptic_ctor)
{
  // get the offset where we'll store our internal c++ class pointer
  OBJ_MEMBER_INT(SELF, elliptic_data_offset) = 0;
  
  // instantiate our internal c++ class representation
  Elliptic * bcdata = new Elliptic(API->vm->get_srate());
  
  // store the pointer in the ChucK object member
  OBJ_MEMBER_INT(SELF, elliptic_data_offset) = (t_CKINT) bcdata;
}


// implementation for the destructor
CK_DLL_DTOR(elliptic_dtor)
{
  // get our c++ class pointer
  Elliptic * bcdata = (Elliptic *) OBJ_MEMBER_INT(SELF, elliptic_data_offset);
  // check it
  if( bcdata )
    {
      // clean up
      delete bcdata;
      OBJ_MEMBER_INT(SELF, elliptic_data_offset) = 0;
      bcdata = NULL;
    }
}


// implementation for tick function
CK_DLL_TICK(elliptic_tick)
{
  // get our c++ class pointer
  Elliptic * c = (Elliptic *) OBJ_MEMBER_INT(SELF, elliptic_data_offset);
  
  // invoke our tick function; store in the magical out variable
  if(c) *out = c->tick(in);
  
  // yes
  return TRUE;
}


// example implementation for setter
CK_DLL_MFUN(elliptic_setParam)
{
  // get our c++ class pointer
  Elliptic * bcdata = (Elliptic *) OBJ_MEMBER_INT(SELF, elliptic_data_offset);
  // set the return value
  RETURN->v_float = bcdata->setParam(GET_NEXT_FLOAT(ARGS));
}


// example implementation for getter
CK_DLL_MFUN(elliptic_getParam)
{
  // get our c++ class pointer
  Elliptic * bcdata = (Elliptic *) OBJ_MEMBER_INT(SELF, elliptic_data_offset);
  // set the return value
  RETURN->v_float = bcdata->getParam();
}
