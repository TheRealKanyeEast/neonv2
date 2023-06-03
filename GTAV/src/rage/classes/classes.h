#pragma once
#include "pch.h"
namespace rage::types {

    struct grcTextureStored {
        char* m_name;
       // ID3D11Resource* m_texture;
       // ID3D11ShaderResourceView* m_shader;
        uint16_t m_width;
        uint16_t m_height;
        uint16_t m_depth;
    };

    struct grcLockedTexture
    {
        int level;
        void* pBits;
        int pitch;
        int pad;
        int width;
        int height;
        int format;
        int numSubLevels;
    };

    enum class grcLockFlags : int
    {
        Read = 1,
        Write = 2,
        Unknown = 4,
        WriteDiscard = 8,
        NoOverwrite = 16
    };

    class grcTexture {
    public:
        virtual ~grcTexture() = NULL;
        virtual bool unk_0008() = NULL;
        virtual int unk_0010() = NULL;
        virtual void unk_0018() = NULL;
        virtual int unk_0020() = NULL;
        virtual uint16_t GetWidth() = NULL;
        virtual uint16_t GetHeight() = NULL;
        virtual uint16_t GetDepth() = NULL;
        virtual uint8_t GetLevels() = NULL;
        virtual void unk_0048() = NULL;
        virtual bool unk_0050() = NULL;
        virtual void unk_0058(int64_t) = NULL;
        virtual void unk_0060(void*) = NULL;
        virtual void unk_0068(void*) = NULL;
        virtual void unk_0070() = NULL;
        virtual rage::types::grcTexture* unk_0078() = NULL;
        virtual rage::types::grcTexture* unk_0080() = NULL;
        virtual bool unk_0088() = NULL;
        virtual int unk_0090() = NULL;
        virtual int unk_0098() = NULL;
        virtual int unk_00A0() = NULL;
        virtual int unk_00A8() = NULL;
        virtual int unk_00B0() = NULL;
        virtual int unk_00B8() = NULL;
        virtual int unk_00C0() = NULL;
        virtual bool Map(int numSubLevels, int subLevel, grcLockedTexture* lockedTexture, grcLockFlags flags) = NULL;

        char pad_0008[32]; //0x0008
        char* m_name; //0x0028
        uint16_t m_ref_count; //0x0030
        uint8_t m_resource_type; //0x0032
        uint8_t m_layers; //0x0033
        char pad_0034[4]; //0x0034
       // ID3D11Resource* m_texture; //0x0038
        uint32_t m_physical_size; //0x0040
        uint32_t m_handle; //0x0044
        uint32_t m_flags; //0x0048
        char pad_004C[4]; //0x004C
        uint16_t m_width; //0x0050
        uint16_t m_height; //0x0052
        uint16_t m_depth; //0x0054
        uint16_t m_mip_stride; //0x0056
        uint32_t m_format; //0x0058
        uint8_t m_image_type; //0x005C
        uint8_t m_mip_count; //0x005D
        uint8_t m_cut_mip_levels; //0x005E
        bool m_is_srgb; //0x005F
        grcTexture* m_previous; //0x0060
        grcTexture* m_next; //0x0068
        void* m_backing; //0x0070
      //  ID3D11ShaderResourceView* m_shader; //0x0078
        char pad_0080[32]; //0x0080
    public:

        void Swap(grcTexture* texure, bool retainOrginialSizes = false) {
           // m_texture = texure->m_texture;
           // m_shader = texure->m_shader;
            if (!retainOrginialSizes) {
                m_width = texure->m_width;
                m_height = texure->m_height;
                m_depth = texure->m_depth;
            }
        }
        void Swap(grcTextureStored texure, bool retainOrginialSizes = false) {
            //m_texture = texure.m_texture;
            //m_shader = texure.m_shader;
            m_width = texure.m_width;
            m_height = texure.m_height;
            m_depth = texure.m_depth;
        }
        grcTextureStored CreateCopy() {
            grcTextureStored data{};
            data.m_name = m_name;
           // data.m_texture = m_texture;
           // data.m_shader = m_shader;
            data.m_width = m_width;
            data.m_height = m_height;
            data.m_depth = m_depth;
            return data;
        }
        void Erase() {
            *(void**)this = nullptr;
        }
    }; //Size: 0x00A0
  //  static_assert(sizeof(grcTexture) == 0xA0);

    class grcRenderTarget : public grcTexture
    {

    };

    struct grcTextureReference
    {
        uint16_t width;
        uint16_t height;
        int format; // also some flags in higher bits
        uint8_t type;
    private:
        uint8_t pad;
        uint16_t pad2;
    public:

        uint16_t stride;
        uint16_t depth;

        uint8_t* pixelData;

        uintptr_t pad3; // 24

        grcTextureReference* nextMipLevel;
        grcTextureReference* nextMajorLevel;
    };

    struct grcManualTextureDef
    {
        // bit flag:
        // | 1 -> dynamic texture (no internal staging texture)
        // | 2 -> unknown
        int isStaging;
        int unk1;
        // flag, sorta:
        // == 0 -> immutable
        // == 1 -> writable?
        // == 2 -> other weird case
        int usage;
        char pad[12];
        int isRenderTarget;
        char pad2[8];
        int arraySize;
        char pad3[16];
    };

    class grcTextureFactory {
    public:
        virtual ~grcTextureFactory() = default;
        virtual grcTexture* unk_0008() = NULL;
        virtual grcTexture* CreateManualTexture() = NULL;
        virtual grcTexture* unk_0018() = NULL;
        virtual grcTexture* CreateTexture(const char* name, int32_t id) = NULL;
        virtual void unk_0028() = NULL;
        virtual void unk_0030() = NULL;
        virtual int TranslateFormatToParamFormat(int32_t format) = NULL;
        virtual void unk_0040() = NULL;
        virtual void unk_0048() = NULL;
        virtual void unk_0050() = NULL;
        virtual void unk_0058() = NULL;
        virtual void unk_0060() = NULL;
        virtual void unk_0068() = NULL;
        virtual void unk_0070() = NULL;
        virtual void unk_0078() = NULL;
        virtual void unk_0080() = NULL;
        virtual void unk_0088() = NULL;
     //   virtual grcTexture* CreateFromNativeTexture(const char* name, ID3D11Resource* nativeResource, void* a3) = NULL;
        virtual void unk_00A0() = NULL;
        virtual void PushRenderTarget(void* a1, grcRenderTarget* target, void* a3, int a4, bool a5, bool a6) = NULL;
        virtual void PopRenderTarget(void* a1, grcRenderTarget* target) = NULL;
    public:
        char pad_0008[8]; //0x0008
    }; //Size: 0x0010
    static_assert(sizeof(grcTextureFactory) == 0x10);

    class pgDictionary {
    public:
        void* m_vtable; //0x0000
        uint64_t unk_0008; //0x0008
        uint64_t unk_0010; //0x0010
        uint32_t unk_0018; //0x0018
        uint32_t unk_001C; //0x001C
        uint64_t unk_0020; //0x0020
        int16_t m_count; //0x0028
        int16_t unk_002A; //0x002A
        char pad_002C[4]; //0x002C
        grcTexture** m_items; //0x0030
        uint32_t unk_0038; //0x0038

        bool AddElement(grcTexture* element) {
            m_count++;
            m_items[m_count - 1] = element;
            return m_items && m_items[m_count - 1] && IsElementValid(m_count - 1);
        }
        bool IsElementValid(uint32_t index) {
            if (!m_items)
                return false;
            if (index >= m_count)
                return false;
            return m_items[index];
        }
        grcTexture* GetElement(uint32_t index) {
            if (IsElementValid(index)) {
                if (m_items[index]->m_name) {
                    return m_items[index];
                }
            }
            return nullptr;
        }
        rage::types::grcTexture* FindTexture(std::string name) {
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    if (!name.compare(element->m_name)) {
                        return element;
                    }
                }
            }
            return nullptr;
        }
        std::vector<std::string> GetAllTextureNames() {
            std::vector<std::string> vec{};
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    vec.push_back(element->m_name);
                }
            }
            return vec;
        }
    }; //Size: 0x003C

    class pgDictionaryPool {
    public:
        pgDictionary* m_dictionary; //0x0000
        char pad_0008[4]; //0x0008
        uint32_t m_dictionary_hash; //0x000C
        char pad_0010[8]; //0x0010
    }; //Size: 0x0018

    class grcTextureStore {
    public:
        char pad_0000[56]; //0x0000
        pgDictionaryPool* m_pool; //0x0038
        uint8_t* m_mask; //0x0040
        uint32_t m_count; //0x0048
        uint32_t m_size; //0x0052
    public:
        auto BitshiftMask(uint32_t index, uint8_t amount) { return m_mask[index] >> amount; }
        bool IsElementValid(uint32_t index) {
            if (!m_mask)
                return false;
            if (index >= m_count)
                return false;
            return ~BitshiftMask(index, 7) & 1;
        }
        pgDictionaryPool* GetElement(uint32_t index) {
            if (IsElementValid(index)) {
                if (m_pool[index].m_dictionary) {
                    return &m_pool[index];
                }
            }
            return nullptr;
        }
        rage::types::pgDictionary* FindDictionary(uint32_t hash) {
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    if (element->m_dictionary_hash == hash) {
                        return element->m_dictionary;
                    }
                }
            }
            return nullptr;
        }
        std::map<uint32_t, rage::types::pgDictionary*> GetAllDictionaries() {
            std::map<uint32_t, rage::types::pgDictionary*> vec{};
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    if (element->m_dictionary_hash) {
                        vec.insert({ element->m_dictionary_hash, element->m_dictionary });
                    }
                }
            }
            return vec;
        }
    }; //Size: 0x0056

    struct guid_pool {
    public:
        char* m_data;
        int8_t* m_flags;
        uint32_t m_max;
        uint32_t m_size;
        uint32_t m_count;

        template<typename T>
        T* get(int index) {
            if (m_flags[index] < 0) return nullptr;
            return (T*)(m_data + (index * m_size));
        }
    };


    struct store_entry {
        uint32_t m_handle;
        uint32_t m_flag;
    };

    struct store_module {
        char _0x0000[0x8];
        uint32_t m_base_index;
        char _0x000C[0x2C];
        guid_pool m_pool;
    };

    struct store_module_manager {};

    struct store_manager {
        store_entry* m_entries;
        char _0x0008[0x1B0];
        store_module_manager m_module;
    };

}

namespace rage {
#pragma pack(push, 1)
    class hash_list
    {
    public:
        std::uint64_t* list; //0x0000
        std::int32_t capacity; //0x0008
        char pad_000C[4]; //0x000C
        std::int32_t free; //0x0010
        char pad_0014[4]; //0x0014
        std::uint64_t item_size; //0x0018
        char pad_0020[16]; //0x0020
        std::uint32_t* data; //0x0030
        char pad_0038[16]; //0x0038
        std::int32_t occupied; //0x0048
        const std::uint64_t get(std::int32_t index) const {
            if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
                return this->list[index];
            return NULL;
        }
    }; // Size: 0x004C
#pragma pack(pop)
}