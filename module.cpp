#include "redismodule.h"
#include "trie.h"

static RedisModuleType *trieModuleType;

int TrieInsert_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc <= 2)
        return RedisModule_WrongArity(ctx);

    RedisModule_AutoMemory(ctx);

    RedisModuleKey *key = (RedisModuleKey *)RedisModule_OpenKey(ctx, argv[1],
                                                                REDISMODULE_READ | REDISMODULE_WRITE);

    int type = RedisModule_KeyType(key);

    if (type != REDISMODULE_KEYTYPE_EMPTY && RedisModule_ModuleTypeGetType(key) != trieModuleType)
        return RedisModule_ReplyWithError(ctx, REDISMODULE_ERRORMSG_WRONGTYPE);

    Trie *trie;

    if (type == REDISMODULE_KEYTYPE_EMPTY)
    {
        trie = new Trie();
        RedisModule_ModuleTypeSetValue(key, trieModuleType, trie);
    }
    else
    {
        trie = (Trie *)RedisModule_ModuleTypeGetValue(key);
    }

    size_t dummy;
    string value = string(RedisModule_StringPtrLen(argv[2], &dummy));

    trie->insert(value);

    RedisModule_ReplyWithLongLong(ctx, 1);
    return REDISMODULE_OK;
}

int TrieSearch_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc <= 2)
        return RedisModule_WrongArity(ctx);

    RedisModule_AutoMemory(ctx);

    RedisModuleKey *key = (RedisModuleKey *)RedisModule_OpenKey(ctx, argv[1],
                                                                REDISMODULE_READ | REDISMODULE_WRITE);

    int type = RedisModule_KeyType(key);

    if (type != REDISMODULE_KEYTYPE_EMPTY && RedisModule_ModuleTypeGetType(key) != trieModuleType)
        return RedisModule_ReplyWithError(ctx, REDISMODULE_ERRORMSG_WRONGTYPE);

    size_t dummy;
    string searchStr = string(RedisModule_StringPtrLen(argv[2], &dummy));

    Trie *trie;

    if (type == REDISMODULE_KEYTYPE_EMPTY)
    {
        RedisModule_ReplyWithLongLong(ctx, 0);
        return REDISMODULE_OK;
    }

    trie = (Trie *)RedisModule_ModuleTypeGetValue(key);

    bool exists = trie->search(searchStr);

    RedisModule_ReplyWithLongLong(ctx, exists ? 1 : 0);
    return REDISMODULE_OK;
}

int TrieRemove_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc <= 2)
        return RedisModule_WrongArity(ctx);

    RedisModule_AutoMemory(ctx);

    RedisModuleKey *key = (RedisModuleKey *)RedisModule_OpenKey(ctx, argv[1],
                                                                REDISMODULE_READ | REDISMODULE_WRITE);

    int type = RedisModule_KeyType(key);

    if (type != REDISMODULE_KEYTYPE_EMPTY && RedisModule_ModuleTypeGetType(key) != trieModuleType)
        return RedisModule_ReplyWithError(ctx, REDISMODULE_ERRORMSG_WRONGTYPE);

    size_t dummy;
    string nodeName = string(RedisModule_StringPtrLen(argv[2], &dummy));

    Trie *trie;

    if (type == REDISMODULE_KEYTYPE_EMPTY)
    {
        RedisModule_ReplyWithLongLong(ctx, 0);
        return REDISMODULE_OK;
    }

    trie = (Trie *)RedisModule_ModuleTypeGetValue(key);
    trie->remove(nodeName);

    RedisModule_ReplyWithLongLong(ctx, 1);
    return REDISMODULE_OK;
}

extern "C" int RedisModule_OnLoad(RedisModuleCtx *ctx)
{
    if (RedisModule_Init(ctx, "trie123az", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    RedisModuleTypeMethods tm = {
        .version = REDISMODULE_TYPE_METHOD_VERSION,
        .rdb_load = NULL,
        .rdb_save = NULL,
        .aof_rewrite = NULL,
        .mem_usage = NULL,
        .free = NULL,
        .digest = NULL};

    trieModuleType = RedisModule_CreateDataType(ctx, "trie123az", 0, &tm);
    if (trieModuleType == NULL)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx, "trie.insert",
                                  TrieInsert_RedisCommand, "write", 1, 1, 1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx, "trie.search",
                                  TrieSearch_RedisCommand, "readonly", 1, 1, 1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx, "trie.remove",
                                  TrieRemove_RedisCommand, "readonly", 1, 1, 1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}