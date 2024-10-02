#pragma once

// Safe Delete
#define DELETE_INSTANCE(pInstance)  \
	if (pInstance)					\
	{								\
		delete (pInstance);			\
		(pInstance) = nullptr;		\
	}

// IUnknown Interface
#define COM_IMPL														\
	HRESULT QueryInterface(const IID& riid, void** ppvObject) override; \
	ULONG AddRef() override;											\
	ULONG Release() override;											\
protected:																\
	DWORD m_dwRefCount = 1;

#define IMPL_COM_FUNC(ClassName)									\
HRESULT ClassName::QueryInterface(const IID& riid, void** ppvObject)\
{																	\
	return E_NOINTERFACE;											\
}																	\
ULONG ClassName::AddRef()											\
{																	\
	return ++m_dwRefCount;											\
}																	\
ULONG ClassName::Release()											\
{																	\
	DWORD	dwRef_count = --m_dwRefCount;							\
	if (!m_dwRefCount)												\
		delete this;												\
	return dwRef_count;												\
}

#define IMPL_COM_FUNC(ClassName)										 \
HRESULT ClassName::QueryInterface(const IID& riid, void** ppvObject)\
{																	\
	return E_NOINTERFACE;											\
}																	\
ULONG ClassName::AddRef()											\
{																	\
	return ++m_dwRefCount;										\
}\
ULONG ClassName::Release()\
{\
	DWORD	dwRef_count = --m_dwRefCount;\
	if (!m_dwRefCount)\
		delete this;\
	return dwRef_count;\
}

// Prevent Copy Constructor
#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

// Singleton Macro
#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static (ClassName)* Get_Instance();					\
	static unsigned long Destroy_Instance();			\
private:												\
	static (ClassName)* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new (ClassName);					\
	return m_pInstance;									\
}

// Error Message
#define ERROR_BOX(MESSAGE) \
	MessageBox(0, TEXT(MESSAGE), TEXT("Error"), MB_OK);\
	__debugbreak();

# define ERROR_CONSOLE \
std::cerr << "##  ERROR  ##:\tFILE " << __FILE__  << "\n\t\t\tLINE " << __LINE__ << ", FUNC " << __FUNCTION__ << "\n\t\t\t"		// Could be augmented for exiting


// PTR
# define CLASS_PTR(ClassName)			\
public:										\
	typedef std::unique_ptr<ClassName>	UPtr;