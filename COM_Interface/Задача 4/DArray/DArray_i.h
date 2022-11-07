

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for DArray.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DArray_i_h__
#define __DArray_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDinArray_FWD_DEFINED__
#define __IDinArray_FWD_DEFINED__
typedef interface IDinArray IDinArray;

#endif 	/* __IDinArray_FWD_DEFINED__ */


#ifndef __DinArray_FWD_DEFINED__
#define __DinArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class DinArray DinArray;
#else
typedef struct DinArray DinArray;
#endif /* __cplusplus */

#endif 	/* __DinArray_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDinArray_INTERFACE_DEFINED__
#define __IDinArray_INTERFACE_DEFINED__

/* interface IDinArray */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDinArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A8F8AEA-B1A0-4667-837F-1091E19D8CA3")
    IDinArray : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ DOUBLE value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ DOUBLE value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [retval][out] */ SAFEARRAY * *arr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_count( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_mean( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDinArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDinArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDinArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDinArray * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDinArray * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDinArray * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDinArray * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDinArray * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDinArray * This,
            /* [in] */ DOUBLE value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IDinArray * This,
            /* [in] */ DOUBLE value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IDinArray * This,
            /* [retval][out] */ SAFEARRAY * *arr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_count )( 
            IDinArray * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mean )( 
            IDinArray * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        END_INTERFACE
    } IDinArrayVtbl;

    interface IDinArray
    {
        CONST_VTBL struct IDinArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDinArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDinArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDinArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDinArray_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDinArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDinArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDinArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDinArray_Add(This,value)	\
    ( (This)->lpVtbl -> Add(This,value) ) 

#define IDinArray_Remove(This,value)	\
    ( (This)->lpVtbl -> Remove(This,value) ) 

#define IDinArray_GetData(This,arr)	\
    ( (This)->lpVtbl -> GetData(This,arr) ) 

#define IDinArray_get_count(This,pVal)	\
    ( (This)->lpVtbl -> get_count(This,pVal) ) 

#define IDinArray_get_mean(This,pVal)	\
    ( (This)->lpVtbl -> get_mean(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDinArray_INTERFACE_DEFINED__ */



#ifndef __DArrayLib_LIBRARY_DEFINED__
#define __DArrayLib_LIBRARY_DEFINED__

/* library DArrayLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_DArrayLib;

EXTERN_C const CLSID CLSID_DinArray;

#ifdef __cplusplus

class DECLSPEC_UUID("F55750AA-AE07-4348-A687-A1BE61989760")
DinArray;
#endif
#endif /* __DArrayLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


