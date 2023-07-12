// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__Centrality
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "src/BordersFinder.h"
#include "src/BordersFinderHelper.h"
#include "src/Getter.h"
#include "src/BordersFinder2D.h"
#include "src/Container.h"
#include "glauber/Fitter.h"
#include "glauber/FitterHelper.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_CentralitycLcLGetter(void *p = nullptr);
   static void *newArray_CentralitycLcLGetter(Long_t size, void *p);
   static void delete_CentralitycLcLGetter(void *p);
   static void deleteArray_CentralitycLcLGetter(void *p);
   static void destruct_CentralitycLcLGetter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Centrality::Getter*)
   {
      ::Centrality::Getter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Centrality::Getter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Centrality::Getter", ::Centrality::Getter::Class_Version(), "src/Getter.h", 21,
                  typeid(::Centrality::Getter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Centrality::Getter::Dictionary, isa_proxy, 4,
                  sizeof(::Centrality::Getter) );
      instance.SetNew(&new_CentralitycLcLGetter);
      instance.SetNewArray(&newArray_CentralitycLcLGetter);
      instance.SetDelete(&delete_CentralitycLcLGetter);
      instance.SetDeleteArray(&deleteArray_CentralitycLcLGetter);
      instance.SetDestructor(&destruct_CentralitycLcLGetter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Centrality::Getter*)
   {
      return GenerateInitInstanceLocal((::Centrality::Getter*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Centrality::Getter*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GlaubercLcLFitter(void *p = nullptr);
   static void *newArray_GlaubercLcLFitter(Long_t size, void *p);
   static void delete_GlaubercLcLFitter(void *p);
   static void deleteArray_GlaubercLcLFitter(void *p);
   static void destruct_GlaubercLcLFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Glauber::Fitter*)
   {
      ::Glauber::Fitter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Glauber::Fitter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Glauber::Fitter", ::Glauber::Fitter::Class_Version(), "glauber/Fitter.h", 82,
                  typeid(::Glauber::Fitter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Glauber::Fitter::Dictionary, isa_proxy, 4,
                  sizeof(::Glauber::Fitter) );
      instance.SetNew(&new_GlaubercLcLFitter);
      instance.SetNewArray(&newArray_GlaubercLcLFitter);
      instance.SetDelete(&delete_GlaubercLcLFitter);
      instance.SetDeleteArray(&deleteArray_GlaubercLcLFitter);
      instance.SetDestructor(&destruct_GlaubercLcLFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Glauber::Fitter*)
   {
      return GenerateInitInstanceLocal((::Glauber::Fitter*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Glauber::Fitter*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace Centrality {
//______________________________________________________________________________
atomic_TClass_ptr Getter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Getter::Class_Name()
{
   return "Centrality::Getter";
}

//______________________________________________________________________________
const char *Getter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Centrality::Getter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Getter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Centrality::Getter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Getter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Centrality::Getter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Getter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Centrality::Getter*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace Centrality
namespace Glauber {
//______________________________________________________________________________
atomic_TClass_ptr Fitter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Fitter::Class_Name()
{
   return "Glauber::Fitter";
}

//______________________________________________________________________________
const char *Fitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Glauber::Fitter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Fitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Glauber::Fitter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Fitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Glauber::Fitter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Fitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Glauber::Fitter*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace Glauber
namespace Centrality {
//______________________________________________________________________________
void Getter::Streamer(TBuffer &R__b)
{
   // Stream an object of class Centrality::Getter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Centrality::Getter::Class(),this);
   } else {
      R__b.WriteClassBuffer(Centrality::Getter::Class(),this);
   }
}

} // namespace Centrality
namespace ROOT {
   // Wrappers around operator new
   static void *new_CentralitycLcLGetter(void *p) {
      return  p ? new(p) ::Centrality::Getter : new ::Centrality::Getter;
   }
   static void *newArray_CentralitycLcLGetter(Long_t nElements, void *p) {
      return p ? new(p) ::Centrality::Getter[nElements] : new ::Centrality::Getter[nElements];
   }
   // Wrapper around operator delete
   static void delete_CentralitycLcLGetter(void *p) {
      delete ((::Centrality::Getter*)p);
   }
   static void deleteArray_CentralitycLcLGetter(void *p) {
      delete [] ((::Centrality::Getter*)p);
   }
   static void destruct_CentralitycLcLGetter(void *p) {
      typedef ::Centrality::Getter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Centrality::Getter

namespace Glauber {
//______________________________________________________________________________
void Fitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class Glauber::Fitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Glauber::Fitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(Glauber::Fitter::Class(),this);
   }
}

} // namespace Glauber
namespace ROOT {
   // Wrappers around operator new
   static void *new_GlaubercLcLFitter(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Glauber::Fitter : new ::Glauber::Fitter;
   }
   static void *newArray_GlaubercLcLFitter(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Glauber::Fitter[nElements] : new ::Glauber::Fitter[nElements];
   }
   // Wrapper around operator delete
   static void delete_GlaubercLcLFitter(void *p) {
      delete ((::Glauber::Fitter*)p);
   }
   static void deleteArray_GlaubercLcLFitter(void *p) {
      delete [] ((::Glauber::Fitter*)p);
   }
   static void destruct_GlaubercLcLFitter(void *p) {
      typedef ::Glauber::Fitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Glauber::Fitter

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = nullptr);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 389,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      ::ROOT::AddClassAlternate("vector<float>","std::vector<float, std::allocator<float> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)nullptr)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEarraylEfloatcO2gRsPgR_Dictionary();
   static void vectorlEarraylEfloatcO2gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEarraylEfloatcO2gRsPgR(void *p = nullptr);
   static void *newArray_vectorlEarraylEfloatcO2gRsPgR(Long_t size, void *p);
   static void delete_vectorlEarraylEfloatcO2gRsPgR(void *p);
   static void deleteArray_vectorlEarraylEfloatcO2gRsPgR(void *p);
   static void destruct_vectorlEarraylEfloatcO2gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<array<float,2> >*)
   {
      vector<array<float,2> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<array<float,2> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<array<float,2> >", -2, "vector", 389,
                  typeid(vector<array<float,2> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEarraylEfloatcO2gRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<array<float,2> >) );
      instance.SetNew(&new_vectorlEarraylEfloatcO2gRsPgR);
      instance.SetNewArray(&newArray_vectorlEarraylEfloatcO2gRsPgR);
      instance.SetDelete(&delete_vectorlEarraylEfloatcO2gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEarraylEfloatcO2gRsPgR);
      instance.SetDestructor(&destruct_vectorlEarraylEfloatcO2gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<array<float,2> > >()));

      ::ROOT::AddClassAlternate("vector<array<float,2> >","std::vector<std::array<float, 2ul>, std::allocator<std::array<float, 2ul> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<array<float,2> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEarraylEfloatcO2gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<array<float,2> >*)nullptr)->GetClass();
      vectorlEarraylEfloatcO2gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEarraylEfloatcO2gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEarraylEfloatcO2gRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<float,2> > : new vector<array<float,2> >;
   }
   static void *newArray_vectorlEarraylEfloatcO2gRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<float,2> >[nElements] : new vector<array<float,2> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEarraylEfloatcO2gRsPgR(void *p) {
      delete ((vector<array<float,2> >*)p);
   }
   static void deleteArray_vectorlEarraylEfloatcO2gRsPgR(void *p) {
      delete [] ((vector<array<float,2> >*)p);
   }
   static void destruct_vectorlEarraylEfloatcO2gRsPgR(void *p) {
      typedef vector<array<float,2> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<array<float,2> >

namespace ROOT {
   static TClass *maplETStringcOfloatgR_Dictionary();
   static void maplETStringcOfloatgR_TClassManip(TClass*);
   static void *new_maplETStringcOfloatgR(void *p = nullptr);
   static void *newArray_maplETStringcOfloatgR(Long_t size, void *p);
   static void delete_maplETStringcOfloatgR(void *p);
   static void deleteArray_maplETStringcOfloatgR(void *p);
   static void destruct_maplETStringcOfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,float>*)
   {
      map<TString,float> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,float>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,float>", -2, "map", 100,
                  typeid(map<TString,float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,float>) );
      instance.SetNew(&new_maplETStringcOfloatgR);
      instance.SetNewArray(&newArray_maplETStringcOfloatgR);
      instance.SetDelete(&delete_maplETStringcOfloatgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOfloatgR);
      instance.SetDestructor(&destruct_maplETStringcOfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,float> >()));

      ::ROOT::AddClassAlternate("map<TString,float>","std::map<TString, float, std::less<TString>, std::allocator<std::pair<TString const, float> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,float>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,float>*)nullptr)->GetClass();
      maplETStringcOfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,float> : new map<TString,float>;
   }
   static void *newArray_maplETStringcOfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,float>[nElements] : new map<TString,float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOfloatgR(void *p) {
      delete ((map<TString,float>*)p);
   }
   static void deleteArray_maplETStringcOfloatgR(void *p) {
      delete [] ((map<TString,float>*)p);
   }
   static void destruct_maplETStringcOfloatgR(void *p) {
      typedef map<TString,float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,float>

namespace ROOT {
   static TClass *maplETStringcOconstsPintgR_Dictionary();
   static void maplETStringcOconstsPintgR_TClassManip(TClass*);
   static void *new_maplETStringcOconstsPintgR(void *p = nullptr);
   static void *newArray_maplETStringcOconstsPintgR(Long_t size, void *p);
   static void delete_maplETStringcOconstsPintgR(void *p);
   static void deleteArray_maplETStringcOconstsPintgR(void *p);
   static void destruct_maplETStringcOconstsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,const int>*)
   {
      map<TString,const int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,const int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,const int>", -2, "map", 100,
                  typeid(map<TString,const int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOconstsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,const int>) );
      instance.SetNew(&new_maplETStringcOconstsPintgR);
      instance.SetNewArray(&newArray_maplETStringcOconstsPintgR);
      instance.SetDelete(&delete_maplETStringcOconstsPintgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOconstsPintgR);
      instance.SetDestructor(&destruct_maplETStringcOconstsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,const int> >()));

      ::ROOT::AddClassAlternate("map<TString,const int>","std::map<TString, int const, std::less<TString>, std::allocator<std::pair<TString const, int const> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,const int>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOconstsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,const int>*)nullptr)->GetClass();
      maplETStringcOconstsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOconstsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOconstsPintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,const int> : new map<TString,const int>;
   }
   static void *newArray_maplETStringcOconstsPintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,const int>[nElements] : new map<TString,const int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOconstsPintgR(void *p) {
      delete ((map<TString,const int>*)p);
   }
   static void deleteArray_maplETStringcOconstsPintgR(void *p) {
      delete [] ((map<TString,const int>*)p);
   }
   static void destruct_maplETStringcOconstsPintgR(void *p) {
      typedef map<TString,const int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,const int>

namespace ROOT {
   static TClass *maplETStringcOTH3FmUgR_Dictionary();
   static void maplETStringcOTH3FmUgR_TClassManip(TClass*);
   static void *new_maplETStringcOTH3FmUgR(void *p = nullptr);
   static void *newArray_maplETStringcOTH3FmUgR(Long_t size, void *p);
   static void delete_maplETStringcOTH3FmUgR(void *p);
   static void deleteArray_maplETStringcOTH3FmUgR(void *p);
   static void destruct_maplETStringcOTH3FmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TH3F*>*)
   {
      map<TString,TH3F*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TH3F*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TH3F*>", -2, "map", 100,
                  typeid(map<TString,TH3F*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOTH3FmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TH3F*>) );
      instance.SetNew(&new_maplETStringcOTH3FmUgR);
      instance.SetNewArray(&newArray_maplETStringcOTH3FmUgR);
      instance.SetDelete(&delete_maplETStringcOTH3FmUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTH3FmUgR);
      instance.SetDestructor(&destruct_maplETStringcOTH3FmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TH3F*> >()));

      ::ROOT::AddClassAlternate("map<TString,TH3F*>","std::map<TString, TH3F*, std::less<TString>, std::allocator<std::pair<TString const, TH3F*> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,TH3F*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTH3FmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TH3F*>*)nullptr)->GetClass();
      maplETStringcOTH3FmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTH3FmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTH3FmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH3F*> : new map<TString,TH3F*>;
   }
   static void *newArray_maplETStringcOTH3FmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH3F*>[nElements] : new map<TString,TH3F*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTH3FmUgR(void *p) {
      delete ((map<TString,TH3F*>*)p);
   }
   static void deleteArray_maplETStringcOTH3FmUgR(void *p) {
      delete [] ((map<TString,TH3F*>*)p);
   }
   static void destruct_maplETStringcOTH3FmUgR(void *p) {
      typedef map<TString,TH3F*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TH3F*>

namespace ROOT {
   static TClass *maplETStringcOTH2FmUgR_Dictionary();
   static void maplETStringcOTH2FmUgR_TClassManip(TClass*);
   static void *new_maplETStringcOTH2FmUgR(void *p = nullptr);
   static void *newArray_maplETStringcOTH2FmUgR(Long_t size, void *p);
   static void delete_maplETStringcOTH2FmUgR(void *p);
   static void deleteArray_maplETStringcOTH2FmUgR(void *p);
   static void destruct_maplETStringcOTH2FmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TH2F*>*)
   {
      map<TString,TH2F*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TH2F*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TH2F*>", -2, "map", 100,
                  typeid(map<TString,TH2F*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOTH2FmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TH2F*>) );
      instance.SetNew(&new_maplETStringcOTH2FmUgR);
      instance.SetNewArray(&newArray_maplETStringcOTH2FmUgR);
      instance.SetDelete(&delete_maplETStringcOTH2FmUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTH2FmUgR);
      instance.SetDestructor(&destruct_maplETStringcOTH2FmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TH2F*> >()));

      ::ROOT::AddClassAlternate("map<TString,TH2F*>","std::map<TString, TH2F*, std::less<TString>, std::allocator<std::pair<TString const, TH2F*> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,TH2F*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTH2FmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TH2F*>*)nullptr)->GetClass();
      maplETStringcOTH2FmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTH2FmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTH2FmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH2F*> : new map<TString,TH2F*>;
   }
   static void *newArray_maplETStringcOTH2FmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH2F*>[nElements] : new map<TString,TH2F*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTH2FmUgR(void *p) {
      delete ((map<TString,TH2F*>*)p);
   }
   static void deleteArray_maplETStringcOTH2FmUgR(void *p) {
      delete [] ((map<TString,TH2F*>*)p);
   }
   static void destruct_maplETStringcOTH2FmUgR(void *p) {
      typedef map<TString,TH2F*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TH2F*>

namespace ROOT {
   static TClass *maplETStringcOTH1FmUgR_Dictionary();
   static void maplETStringcOTH1FmUgR_TClassManip(TClass*);
   static void *new_maplETStringcOTH1FmUgR(void *p = nullptr);
   static void *newArray_maplETStringcOTH1FmUgR(Long_t size, void *p);
   static void delete_maplETStringcOTH1FmUgR(void *p);
   static void deleteArray_maplETStringcOTH1FmUgR(void *p);
   static void destruct_maplETStringcOTH1FmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TH1F*>*)
   {
      map<TString,TH1F*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TH1F*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TH1F*>", -2, "map", 100,
                  typeid(map<TString,TH1F*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOTH1FmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TH1F*>) );
      instance.SetNew(&new_maplETStringcOTH1FmUgR);
      instance.SetNewArray(&newArray_maplETStringcOTH1FmUgR);
      instance.SetDelete(&delete_maplETStringcOTH1FmUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTH1FmUgR);
      instance.SetDestructor(&destruct_maplETStringcOTH1FmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TH1F*> >()));

      ::ROOT::AddClassAlternate("map<TString,TH1F*>","std::map<TString, TH1F*, std::less<TString>, std::allocator<std::pair<TString const, TH1F*> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<TString,TH1F*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTH1FmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TH1F*>*)nullptr)->GetClass();
      maplETStringcOTH1FmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTH1FmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTH1FmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH1F*> : new map<TString,TH1F*>;
   }
   static void *newArray_maplETStringcOTH1FmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TH1F*>[nElements] : new map<TString,TH1F*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTH1FmUgR(void *p) {
      delete ((map<TString,TH1F*>*)p);
   }
   static void deleteArray_maplETStringcOTH1FmUgR(void *p) {
      delete [] ((map<TString,TH1F*>*)p);
   }
   static void destruct_maplETStringcOTH1FmUgR(void *p) {
      typedef map<TString,TH1F*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TH1F*>

namespace {
  void TriggerDictionaryInitialization_libCentrality_Impl() {
    static const char* headers[] = {
"src/BordersFinder.h",
"src/BordersFinderHelper.h",
"src/Getter.h",
"src/BordersFinder2D.h",
"src/Container.h",
"glauber/Fitter.h",
"glauber/FitterHelper.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/isegal/root/include",
"/home/isegal/CentralityFramework/centrality-master",
"/home/isegal/root/include/",
"/home/isegal/CentralityFramework/centrality-master/build/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libCentrality dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace Centrality{class __attribute__((annotate("$clingAutoload$src/BordersFinderHelper.h")))  Getter;}
namespace Glauber{class __attribute__((annotate("$clingAutoload$glauber/Fitter.h")))  Fitter;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libCentrality dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/BordersFinder.h"
#include "src/BordersFinderHelper.h"
#include "src/Getter.h"
#include "src/BordersFinder2D.h"
#include "src/Container.h"
#include "glauber/Fitter.h"
#include "glauber/FitterHelper.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Centrality::Getter", payloadCode, "@",
"Glauber::Fitter", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libCentrality",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libCentrality_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libCentrality_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libCentrality() {
  TriggerDictionaryInitialization_libCentrality_Impl();
}
