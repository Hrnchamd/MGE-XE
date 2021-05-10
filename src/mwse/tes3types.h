
namespace TES3 {

struct MWEntity : MWRecord {
    char other[0x18];
    const float* bounds;
    const char* name;
};

struct Node {
    const void** vtbl;
    char stuff[0x10];
    unsigned short flags;
    unsigned short pad;
    Node* parent;
    float boundOrigin[3];
    float boundRadius;
    float* pLocalRotate;
    float localTranslate[3];
    float localScale;
    float worldRotate[9];
    float worldTranslate[3];
    float worldScale;
    char various[0x28];
    void* skinInstance;
};

struct Pick {
    struct Record {
        Node* spObject;
        Node* spProxyParent;
        float intersect[3];
        float distance;
        unsigned short usTriangleIndex;
        unsigned short usVertexIndex[3];
        float texture[2];
        float normal[3];
        unsigned char color[4];
    };
    struct Results {
        void** vtbl;
        Record** data;
        size_t storageCount;
        size_t endIndex;
        size_t filledCount;
        size_t growByCount;
    };

    int ePickType;
    int eSortType;
    int eIntersectType;
    int eCoordinateType;
    bool bFrontOnly;
    bool bObserveAppCullFlag;
    void* spRoot;
    Results pickResults;
    Record* pLastAddedRecord;
    bool bReturnTexture;
    bool bReturnNormal;
    bool bReturnSmoothNormal;
    bool bReturnColor;
};

}
