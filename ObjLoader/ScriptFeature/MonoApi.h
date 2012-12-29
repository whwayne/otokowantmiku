#pragma once
typedef unsigned int guint32;
#include "MonoType.h"



#define ALL_MONO_API \
MONO_API(MonoDomain* , mono_jit_init_version ,(const char* root_domain_name,const char* runtime_version))\
MONO_API(MonoDomain* , mono_domain_get ,())\
MONO_API(MonoAssembly*,mono_domain_assembly_open, (MonoDomain *domain, const char *name))\
MONO_API( MonoImage* , mono_assembly_get_image ,     (MonoAssembly *assembly))\
MONO_API( MonoObject* ,mono_runtime_invoke, (MonoMethod *method, void *obj, void **params, MonoObject **exc))\
MONO_API( MonoClass* , mono_class_from_name_case ,(MonoImage *image, const char* name_space, const char *name))\
MONO_API( MonoClass* , mono_class_from_name ,(MonoImage *image, const char* name_space, const char *name))\
MONO_API( MonoObject* ,mono_object_new, (MonoDomain *domain, MonoClass *klass))\
MONO_API( MonoClass* , mono_object_get_class, (MonoObject *obj))\
MONO_API( void ,	   mono_runtime_object_init, (MonoObject *obj))\
MONO_API( void ,	   mono_add_internal_call,(char* desc, void* ftnptr))\
MONO_API( guint32 ,    mono_gchandle_new  ,       (MonoObject *obj,  int pinned))\
MONO_API( guint32 ,    mono_gchandle_new_weakref ,(MonoObject *obj,  int track_resurrection))\
MONO_API( MonoObject*, mono_gchandle_get_target,  (guint32 gchandle))\
MONO_API( void   ,     mono_gchandle_free   ,     (guint32 gchandle))\
MONO_API( void   ,     mono_set_dirs   ,    (const char *assembly_dir, const char *config_dir))\

#undef MONO_API
#define MONO_API(r,n,p) extern r (*n) p;
ALL_MONO_API