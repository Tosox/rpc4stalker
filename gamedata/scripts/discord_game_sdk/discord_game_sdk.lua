local ffi = require("ffi")
local game_sdk = ffi.load("discord_game_sdk")

-- Support for x86 as well as x64
local DISCORD_API = ""
if (ffi.os == "Windows") and (not (ffi.arch == "x64")) then
	DISCORD_API = "__stdcall"
end

local discord_game_sdk_h = {
[[
typedef void IDXGISwapChain;
typedef void MSG;

void free(void *ptr);
void *malloc(size_t size);
void *memset(void *s, int c, size_t n);
	
enum{DISCORD_VERSION = 3};
enum{DISCORD_APPLICATION_MANAGER_VERSION = 1};
enum{DISCORD_USER_MANAGER_VERSION = 1};
enum{DISCORD_IMAGE_MANAGER_VERSION = 1};
enum{DISCORD_ACTIVITY_MANAGER_VERSION = 1};
enum{DISCORD_RELATIONSHIP_MANAGER_VERSION = 1};
enum{DISCORD_LOBBY_MANAGER_VERSION = 1};
enum{DISCORD_NETWORK_MANAGER_VERSION = 1};
enum{DISCORD_OVERLAY_MANAGER_VERSION = 2};
enum{DISCORD_STORAGE_MANAGER_VERSION = 1};
enum{DISCORD_STORE_MANAGER_VERSION = 1};
enum{DISCORD_VOICE_MANAGER_VERSION = 1};
enum{DISCORD_ACHIEVEMENT_MANAGER_VERSION = 1};

enum EDiscordResult {
	DiscordResult_Ok = 0,
	DiscordResult_ServiceUnavailable = 1,
	DiscordResult_InvalidVersion = 2,
	DiscordResult_LockFailed = 3,
	DiscordResult_InternalError = 4,
	DiscordResult_InvalidPayload = 5,
	DiscordResult_InvalidCommand = 6,
	DiscordResult_InvalidPermissions = 7,
	DiscordResult_NotFetched = 8,
	DiscordResult_NotFound = 9,
	DiscordResult_Conflict = 10,
	DiscordResult_InvalidSecret = 11,
	DiscordResult_InvalidJoinSecret = 12,
	DiscordResult_NoEligibleActivity = 13,
	DiscordResult_InvalidInvite = 14,
	DiscordResult_NotAuthenticated = 15,
	DiscordResult_InvalidAccessToken = 16,
	DiscordResult_ApplicationMismatch = 17,
	DiscordResult_InvalidDataUrl = 18,
	DiscordResult_InvalidBase64 = 19,
	DiscordResult_NotFiltered = 20,
	DiscordResult_LobbyFull = 21,
	DiscordResult_InvalidLobbySecret = 22,
	DiscordResult_InvalidFilename = 23,
	DiscordResult_InvalidFileSize = 24,
	DiscordResult_InvalidEntitlement = 25,
	DiscordResult_NotInstalled = 26,
	DiscordResult_NotRunning = 27,
	DiscordResult_InsufficientBuffer = 28,
	DiscordResult_PurchaseCanceled = 29,
	DiscordResult_InvalidGuild = 30,
	DiscordResult_InvalidEvent = 31,
	DiscordResult_InvalidChannel = 32,
	DiscordResult_InvalidOrigin = 33,
	DiscordResult_RateLimited = 34,
	DiscordResult_OAuth2Error = 35,
	DiscordResult_SelectChannelTimeout = 36,
	DiscordResult_GetGuildTimeout = 37,
	DiscordResult_SelectVoiceForceRequired = 38,
	DiscordResult_CaptureShortcutAlreadyListening = 39,
	DiscordResult_UnauthorizedForAchievement = 40,
	DiscordResult_InvalidGiftCode = 41,
	DiscordResult_PurchaseError = 42,
	DiscordResult_TransactionAborted = 43,
	DiscordResult_DrawingInitFailed = 44,
};

enum EDiscordCreateFlags {
	DiscordCreateFlags_Default = 0,
	DiscordCreateFlags_NoRequireDiscord = 1,
};

enum EDiscordLogLevel {
	DiscordLogLevel_Error = 1,
	DiscordLogLevel_Warn,
	DiscordLogLevel_Info,
	DiscordLogLevel_Debug,
};

enum EDiscordUserFlag {
	DiscordUserFlag_Partner = 2,
	DiscordUserFlag_HypeSquadEvents = 4,
	DiscordUserFlag_HypeSquadHouse1 = 64,
	DiscordUserFlag_HypeSquadHouse2 = 128,
	DiscordUserFlag_HypeSquadHouse3 = 256,
};

enum EDiscordPremiumType {
	DiscordPremiumType_None = 0,
	DiscordPremiumType_Tier1 = 1,
	DiscordPremiumType_Tier2 = 2,
};

enum EDiscordImageType {
	DiscordImageType_User,
};

enum EDiscordActivityPartyPrivacy {
	DiscordActivityPartyPrivacy_Private = 0,
	DiscordActivityPartyPrivacy_Public = 1,
};

enum EDiscordActivityType {
	DiscordActivityType_Playing,
	DiscordActivityType_Streaming,
	DiscordActivityType_Listening,
	DiscordActivityType_Watching,
};

enum EDiscordActivityActionType {
	DiscordActivityActionType_Join = 1,
	DiscordActivityActionType_Spectate,
};

enum EDiscordActivitySupportedPlatformFlags {
	DiscordActivitySupportedPlatformFlags_Desktop = 1,
	DiscordActivitySupportedPlatformFlags_Android = 2,
	DiscordActivitySupportedPlatformFlags_iOS = 4,
};

enum EDiscordActivityJoinRequestReply {
	DiscordActivityJoinRequestReply_No,
	DiscordActivityJoinRequestReply_Yes,
	DiscordActivityJoinRequestReply_Ignore,
};

enum EDiscordStatus {
	DiscordStatus_Offline = 0,
	DiscordStatus_Online = 1,
	DiscordStatus_Idle = 2,
	DiscordStatus_DoNotDisturb = 3,
};

enum EDiscordRelationshipType {
	DiscordRelationshipType_None,
	DiscordRelationshipType_Friend,
	DiscordRelationshipType_Blocked,
	DiscordRelationshipType_PendingIncoming,
	DiscordRelationshipType_PendingOutgoing,
	DiscordRelationshipType_Implicit,
};

enum EDiscordLobbyType {
	DiscordLobbyType_Private = 1,
	DiscordLobbyType_Public,
};

enum EDiscordLobbySearchComparison {
	DiscordLobbySearchComparison_LessThanOrEqual = -2,
	DiscordLobbySearchComparison_LessThan,
	DiscordLobbySearchComparison_Equal,
	DiscordLobbySearchComparison_GreaterThan,
	DiscordLobbySearchComparison_GreaterThanOrEqual,
	DiscordLobbySearchComparison_NotEqual,
};

enum EDiscordLobbySearchCast {
	DiscordLobbySearchCast_String = 1,
	DiscordLobbySearchCast_Number,
};

enum EDiscordLobbySearchDistance {
	DiscordLobbySearchDistance_Local,
	DiscordLobbySearchDistance_Default,
	DiscordLobbySearchDistance_Extended,
	DiscordLobbySearchDistance_Global,
};

enum EDiscordKeyVariant {
	DiscordKeyVariant_Normal,
	DiscordKeyVariant_Right,
	DiscordKeyVariant_Left,
};

enum EDiscordMouseButton {
	DiscordMouseButton_Left,
	DiscordMouseButton_Middle,
	DiscordMouseButton_Right,
};

enum EDiscordEntitlementType {
	DiscordEntitlementType_Purchase = 1,
	DiscordEntitlementType_PremiumSubscription,
	DiscordEntitlementType_DeveloperGift,
	DiscordEntitlementType_TestModePurchase,
	DiscordEntitlementType_FreePurchase,
	DiscordEntitlementType_UserGift,
	DiscordEntitlementType_PremiumPurchase,
};

enum EDiscordSkuType {
	DiscordSkuType_Application = 1,
	DiscordSkuType_DLC,
	DiscordSkuType_Consumable,
	DiscordSkuType_Bundle,
};

enum EDiscordInputModeType {
	DiscordInputModeType_VoiceActivity = 0,
	DiscordInputModeType_PushToTalk,
};

typedef int64_t DiscordClientId;
typedef int32_t DiscordVersion;
typedef int64_t DiscordSnowflake;
typedef int64_t DiscordTimestamp;
typedef DiscordSnowflake DiscordUserId;
typedef char DiscordLocale[128];
typedef char DiscordBranch[4096];
typedef DiscordSnowflake DiscordLobbyId;
typedef char DiscordLobbySecret[128];
typedef char DiscordMetadataKey[256];
typedef char DiscordMetadataValue[4096];
typedef uint64_t DiscordNetworkPeerId;
typedef uint8_t DiscordNetworkChannelId;
typedef char DiscordPath[4096];
typedef char DiscordDateTime[64];

struct DiscordUser {
	DiscordUserId id;
	char username[256];
	char discriminator[8];
	char avatar[128];
	bool bot;
};

struct DiscordOAuth2Token {
	char access_token[128];
	char scopes[1024];
	DiscordTimestamp expires;
};

struct DiscordImageHandle {
	enum EDiscordImageType type;
	int64_t id;
	uint32_t size;
};

struct DiscordImageDimensions {
	uint32_t width;
	uint32_t height;
};


struct DiscordActivityTimestamps {
	DiscordTimestamp start;
	DiscordTimestamp end;
};

struct DiscordActivityAssets {
	char large_image[128];
	char large_text[128];
	char small_image[128];
	char small_text[128];
};

struct DiscordPartySize {
	int32_t current_size;
	int32_t max_size;
};

struct DiscordActivityParty {
	char id[128];
	struct DiscordPartySize size;
	enum EDiscordActivityPartyPrivacy privacy;
};

struct DiscordActivitySecrets {
	char match[128];
	char join[128];
	char spectate[128];
};

struct DiscordActivity {
	enum EDiscordActivityType type;
	int64_t application_id;
	char name[128];
	char state[128];
	char details[128];
	struct DiscordActivityTimestamps timestamps;
	struct DiscordActivityAssets assets;
	struct DiscordActivityParty party;
	struct DiscordActivitySecrets secrets;
	bool instance;
	uint32_t supported_platforms;
};

struct DiscordPresence {
	enum EDiscordStatus status;
	struct DiscordActivity activity;
};

struct DiscordRelationship {
	enum EDiscordRelationshipType type;
	struct DiscordUser user;
	struct DiscordPresence presence;
};

struct DiscordLobby {
	DiscordLobbyId id;
	enum EDiscordLobbyType type;
	DiscordUserId owner_id;
	DiscordLobbySecret secret;
	uint32_t capacity;
	bool locked;
};

struct DiscordImeUnderline {
	int32_t from;
	int32_t to;
	uint32_t color;
	uint32_t background_color;
	bool thick;
};

struct DiscordRect {
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
};

struct DiscordFileStat {
	char filename[260];
	uint64_t size;
	uint64_t last_modified;
};

struct DiscordEntitlement {
	DiscordSnowflake id;
	enum EDiscordEntitlementType type;
	DiscordSnowflake sku_id;
};

struct DiscordSkuPrice {
	uint32_t amount;
	char currency[16];
};

struct DiscordSku {
	DiscordSnowflake id;
	enum EDiscordSkuType type;
	char name[256];
	struct DiscordSkuPrice price;
};

struct DiscordInputMode {
	enum EDiscordInputModeType type;
	char shortcut[256];
};

struct DiscordUserAchievement {
	DiscordSnowflake user_id;
	DiscordSnowflake achievement_id;
	uint8_t percent_complete;
	DiscordDateTime unlocked_at;
};

struct IDiscordLobbyTransaction {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_type)(struct IDiscordLobbyTransaction* lobby_transaction, enum EDiscordLobbyType type);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_owner)(struct IDiscordLobbyTransaction* lobby_transaction, DiscordUserId owner_id);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_capacity)(struct IDiscordLobbyTransaction* lobby_transaction, uint32_t capacity);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_metadata)(struct IDiscordLobbyTransaction* lobby_transaction, DiscordMetadataKey key, DiscordMetadataValue value);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *delete_metadata)(struct IDiscordLobbyTransaction* lobby_transaction, DiscordMetadataKey key);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_locked)(struct IDiscordLobbyTransaction* lobby_transaction, bool locked);
};

struct IDiscordLobbyMemberTransaction {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_metadata)(struct IDiscordLobbyMemberTransaction* lobby_member_transaction, DiscordMetadataKey key, DiscordMetadataValue value);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *delete_metadata)(struct IDiscordLobbyMemberTransaction* lobby_member_transaction, DiscordMetadataKey key);
};

struct IDiscordLobbySearchQuery {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *filter)(struct IDiscordLobbySearchQuery* lobby_search_query, DiscordMetadataKey key, enum EDiscordLobbySearchComparison comparison, enum EDiscordLobbySearchCast cast, DiscordMetadataValue value);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *sort)(struct IDiscordLobbySearchQuery* lobby_search_query, DiscordMetadataKey key, enum EDiscordLobbySearchCast cast, DiscordMetadataValue value);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *limit)(struct IDiscordLobbySearchQuery* lobby_search_query, uint32_t limit);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *distance)(struct IDiscordLobbySearchQuery* lobby_search_query, enum EDiscordLobbySearchDistance distance);
};

typedef void* IDiscordApplicationEvents;

struct IDiscordApplicationManager {
	void (]] .. DISCORD_API .. [[ *validate_or_exit)(struct IDiscordApplicationManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *get_current_locale)(struct IDiscordApplicationManager* manager, DiscordLocale* locale);
	void (]] .. DISCORD_API .. [[ *get_current_branch)(struct IDiscordApplicationManager* manager, DiscordBranch* branch);
	void (]] .. DISCORD_API .. [[ *get_oauth2_token)(struct IDiscordApplicationManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, struct DiscordOAuth2Token* oauth2_token));
	void (]] .. DISCORD_API .. [[ *get_ticket)(struct IDiscordApplicationManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, const char* data));
};

struct IDiscordUserEvents {
	void (]] .. DISCORD_API .. [[ *on_current_user_update)(void* event_data);
};

struct IDiscordUserManager {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_current_user)(struct IDiscordUserManager* manager, struct DiscordUser* current_user);
	void (]] .. DISCORD_API .. [[ *get_user)(struct IDiscordUserManager* manager, DiscordUserId user_id, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, struct DiscordUser* user));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_current_user_premium_type)(struct IDiscordUserManager* manager, enum EDiscordPremiumType* premium_type);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *current_user_has_flag)(struct IDiscordUserManager* manager, enum EDiscordUserFlag flag, bool* has_flag);
};

typedef void* IDiscordImageEvents;

struct IDiscordImageManager {
	void (]] .. DISCORD_API .. [[ *fetch)(struct IDiscordImageManager* manager, struct DiscordImageHandle handle, bool refresh, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, struct DiscordImageHandle handle_result));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_dimensions)(struct IDiscordImageManager* manager, struct DiscordImageHandle handle, struct DiscordImageDimensions* dimensions);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_data)(struct IDiscordImageManager* manager, struct DiscordImageHandle handle, uint8_t* data, uint32_t data_length);
};

struct IDiscordActivityEvents {
	void (]] .. DISCORD_API .. [[ *on_activity_join)(void* event_data, const char* secret);
	void (]] .. DISCORD_API .. [[ *on_activity_spectate)(void* event_data, const char* secret);
	void (]] .. DISCORD_API .. [[ *on_activity_join_request)(void* event_data, struct DiscordUser* user);
	void (]] .. DISCORD_API .. [[ *on_activity_invite)(void* event_data, enum EDiscordActivityActionType type, struct DiscordUser* user, struct DiscordActivity* activity);
};

struct IDiscordActivityManager {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *register_command)(struct IDiscordActivityManager* manager, const char* command);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *register_steam)(struct IDiscordActivityManager* manager, uint32_t steam_id);
	void (]] .. DISCORD_API .. [[ *update_activity)(struct IDiscordActivityManager* manager, struct DiscordActivity* activity, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *clear_activity)(struct IDiscordActivityManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *send_request_reply)(struct IDiscordActivityManager* manager, DiscordUserId user_id, enum EDiscordActivityJoinRequestReply reply, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *send_invite)(struct IDiscordActivityManager* manager, DiscordUserId user_id, enum EDiscordActivityActionType type, const char* content, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *accept_invite)(struct IDiscordActivityManager* manager, DiscordUserId user_id, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
};

struct IDiscordRelationshipEvents {
	void (]] .. DISCORD_API .. [[ *on_refresh)(void* event_data);
	void (]] .. DISCORD_API .. [[ *on_relationship_update)(void* event_data, struct DiscordRelationship* relationship);
};

struct IDiscordRelationshipManager {
	void (]] .. DISCORD_API .. [[ *filter)(struct IDiscordRelationshipManager* manager, void* filter_data, bool (]] .. DISCORD_API .. [[ *filter)(void* filter_data, struct DiscordRelationship* relationship));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *count)(struct IDiscordRelationshipManager* manager, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get)(struct IDiscordRelationshipManager* manager, DiscordUserId user_id, struct DiscordRelationship* relationship);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_at)(struct IDiscordRelationshipManager* manager, uint32_t index, struct DiscordRelationship* relationship);
};

struct IDiscordLobbyEvents {
	void (]] .. DISCORD_API .. [[ *on_lobby_update)(void* event_data, int64_t lobby_id);
	void (]] .. DISCORD_API .. [[ *on_lobby_delete)(void* event_data, int64_t lobby_id, uint32_t reason);
	void (]] .. DISCORD_API .. [[ *on_member_connect)(void* event_data, int64_t lobby_id, int64_t user_id);
	void (]] .. DISCORD_API .. [[ *on_member_update)(void* event_data, int64_t lobby_id, int64_t user_id);
	void (]] .. DISCORD_API .. [[ *on_member_disconnect)(void* event_data, int64_t lobby_id, int64_t user_id);
	void (]] .. DISCORD_API .. [[ *on_lobby_message)(void* event_data, int64_t lobby_id, int64_t user_id, uint8_t* data, uint32_t data_length);
	void (]] .. DISCORD_API .. [[ *on_speaking)(void* event_data, int64_t lobby_id, int64_t user_id, bool speaking);
	void (]] .. DISCORD_API .. [[ *on_network_message)(void* event_data, int64_t lobby_id, int64_t user_id, uint8_t channel_id, uint8_t* data, uint32_t data_length);
};
]],
[[
struct IDiscordLobbyManager {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_lobby_create_transaction)(struct IDiscordLobbyManager* manager, struct IDiscordLobbyTransaction** transaction);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_lobby_update_transaction)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, struct IDiscordLobbyTransaction** transaction);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_member_update_transaction)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordUserId user_id, struct IDiscordLobbyMemberTransaction** transaction);
	void (]] .. DISCORD_API .. [[ *create_lobby)(struct IDiscordLobbyManager* manager, struct IDiscordLobbyTransaction* transaction, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, struct DiscordLobby* lobby));
	void (]] .. DISCORD_API .. [[ *update_lobby)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, struct IDiscordLobbyTransaction* transaction, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *delete_lobby)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *connect_lobby)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordLobbySecret secret, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, struct DiscordLobby* lobby));
	void (]] .. DISCORD_API .. [[ *connect_lobby_with_activity_secret)(struct IDiscordLobbyManager* manager, DiscordLobbySecret activity_secret, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, struct DiscordLobby* lobby));
	void (]] .. DISCORD_API .. [[ *disconnect_lobby)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_lobby)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, struct DiscordLobby* lobby);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_lobby_activity_secret)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordLobbySecret* secret);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_lobby_metadata_value)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordMetadataKey key, DiscordMetadataValue* value);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_lobby_metadata_key)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, int32_t index, DiscordMetadataKey* key);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *lobby_metadata_count)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *member_count)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_member_user_id)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, int32_t index, DiscordUserId* user_id);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_member_user)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordUserId user_id, struct DiscordUser* user);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_member_metadata_value)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordUserId user_id, DiscordMetadataKey key, DiscordMetadataValue* value);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_member_metadata_key)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordUserId user_id, int32_t index, DiscordMetadataKey* key);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *member_metadata_count)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordUserId user_id, int32_t* count);
	void (]] .. DISCORD_API .. [[ *update_member)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordUserId user_id, struct IDiscordLobbyMemberTransaction* transaction, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *send_lobby_message)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, uint8_t* data, uint32_t data_length, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_search_query)(struct IDiscordLobbyManager* manager, struct IDiscordLobbySearchQuery** query);
	void (]] .. DISCORD_API .. [[ *search)(struct IDiscordLobbyManager* manager, struct IDiscordLobbySearchQuery* query, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *lobby_count)(struct IDiscordLobbyManager* manager, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_lobby_id)(struct IDiscordLobbyManager* manager, int32_t index, DiscordLobbyId* lobby_id);
	void (]] .. DISCORD_API .. [[ *connect_voice)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *disconnect_voice)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *connect_network)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *disconnect_network)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *flush_network)(struct IDiscordLobbyManager* manager);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *open_network_channel)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, uint8_t channel_id, bool reliable);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *send_network_message)(struct IDiscordLobbyManager* manager, DiscordLobbyId lobby_id, DiscordUserId user_id, uint8_t channel_id, uint8_t* data, uint32_t data_length);
};

struct IDiscordNetworkEvents {
	void (]] .. DISCORD_API .. [[ *on_message)(void* event_data, DiscordNetworkPeerId peer_id, DiscordNetworkChannelId channel_id, uint8_t* data, uint32_t data_length);
	void (]] .. DISCORD_API .. [[ *on_route_update)(void* event_data, const char* route_data);
};

struct IDiscordNetworkManager {
	/**
	 * Get the local peer ID for this process.
	 */
	void (]] .. DISCORD_API .. [[ *get_peer_id)(struct IDiscordNetworkManager* manager, DiscordNetworkPeerId* peer_id);
	/**
	 * Send pending network messages.
	 */
	enum EDiscordResult (]] .. DISCORD_API .. [[ *flush)(struct IDiscordNetworkManager* manager);
	/**
	 * Open a connection to a remote peer.
	 */
	enum EDiscordResult (]] .. DISCORD_API .. [[ *open_peer)(struct IDiscordNetworkManager* manager, DiscordNetworkPeerId peer_id, const char* route_data);
	/**
	 * Update the route data for a connected peer.
	 */
	enum EDiscordResult (]] .. DISCORD_API .. [[ *update_peer)(struct IDiscordNetworkManager* manager, DiscordNetworkPeerId peer_id, const char* route_data);
	/**
	 * Close the connection to a remote peer.
	 */
	enum EDiscordResult (]] .. DISCORD_API .. [[ *close_peer)(struct IDiscordNetworkManager* manager, DiscordNetworkPeerId peer_id);
	/**
	 * Open a message channel to a connected peer.
	 */
	enum EDiscordResult (]] .. DISCORD_API .. [[ *open_channel)(struct IDiscordNetworkManager* manager, DiscordNetworkPeerId peer_id, DiscordNetworkChannelId channel_id, bool reliable);
	/**
	 * Close a message channel to a connected peer.
	 */
	enum EDiscordResult (]] .. DISCORD_API .. [[ *close_channel)(struct IDiscordNetworkManager* manager, DiscordNetworkPeerId peer_id, DiscordNetworkChannelId channel_id);
	/**
	 * Send a message to a connected peer over an opened message channel.
	 */
	enum EDiscordResult (]] .. DISCORD_API .. [[ *send_message)(struct IDiscordNetworkManager* manager, DiscordNetworkPeerId peer_id, DiscordNetworkChannelId channel_id, uint8_t* data, uint32_t data_length);
};

struct IDiscordOverlayEvents {
	void (]] .. DISCORD_API .. [[ *on_toggle)(void* event_data, bool locked);
};

struct IDiscordOverlayManager {
	void (]] .. DISCORD_API .. [[ *is_enabled)(struct IDiscordOverlayManager* manager, bool* enabled);
	void (]] .. DISCORD_API .. [[ *is_locked)(struct IDiscordOverlayManager* manager, bool* locked);
	void (]] .. DISCORD_API .. [[ *set_locked)(struct IDiscordOverlayManager* manager, bool locked, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *open_activity_invite)(struct IDiscordOverlayManager* manager, enum EDiscordActivityActionType type, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *open_guild_invite)(struct IDiscordOverlayManager* manager, const char* code, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *open_voice_settings)(struct IDiscordOverlayManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *init_drawing_dxgi)(struct IDiscordOverlayManager* manager, IDXGISwapChain* swapchain, bool use_message_forwarding);
	void (]] .. DISCORD_API .. [[ *on_present)(struct IDiscordOverlayManager* manager);
	void (]] .. DISCORD_API .. [[ *forward_message)(struct IDiscordOverlayManager* manager, MSG* message);
	void (]] .. DISCORD_API .. [[ *key_event)(struct IDiscordOverlayManager* manager, bool down, const char* key_code, enum EDiscordKeyVariant variant);
	void (]] .. DISCORD_API .. [[ *char_event)(struct IDiscordOverlayManager* manager, const char* character);
	void (]] .. DISCORD_API .. [[ *mouse_button_event)(struct IDiscordOverlayManager* manager, uint8_t down, int32_t click_count, enum EDiscordMouseButton which, int32_t x, int32_t y);
	void (]] .. DISCORD_API .. [[ *mouse_motion_event)(struct IDiscordOverlayManager* manager, int32_t x, int32_t y);
	void (]] .. DISCORD_API .. [[ *ime_commit_text)(struct IDiscordOverlayManager* manager, const char* text);
	void (]] .. DISCORD_API .. [[ *ime_set_composition)(struct IDiscordOverlayManager* manager, const char* text, struct DiscordImeUnderline* underlines, uint32_t underlines_length, int32_t from, int32_t to);
	void (]] .. DISCORD_API .. [[ *ime_cancel_composition)(struct IDiscordOverlayManager* manager);
	void (]] .. DISCORD_API .. [[ *set_ime_composition_range_callback)(struct IDiscordOverlayManager* manager, void* on_ime_composition_range_changed_data, void (]] .. DISCORD_API .. [[ *on_ime_composition_range_changed)(void* on_ime_composition_range_changed_data, int32_t from, int32_t to, struct DiscordRect* bounds, uint32_t bounds_length));
	void (]] .. DISCORD_API .. [[ *set_ime_selection_bounds_callback)(struct IDiscordOverlayManager* manager, void* on_ime_selection_bounds_changed_data, void (]] .. DISCORD_API .. [[ *on_ime_selection_bounds_changed)(void* on_ime_selection_bounds_changed_data, struct DiscordRect anchor, struct DiscordRect focus, bool is_anchor_first));
	bool (]] .. DISCORD_API .. [[ *is_point_inside_click_zone)(struct IDiscordOverlayManager* manager, int32_t x, int32_t y);
};

typedef void* IDiscordStorageEvents;

struct IDiscordStorageManager {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *read)(struct IDiscordStorageManager* manager, const char* name, uint8_t* data, uint32_t data_length, uint32_t* read);
	void (]] .. DISCORD_API .. [[ *read_async)(struct IDiscordStorageManager* manager, const char* name, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, uint8_t* data, uint32_t data_length));
	void (]] .. DISCORD_API .. [[ *read_async_partial)(struct IDiscordStorageManager* manager, const char* name, uint64_t offset, uint64_t length, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result, uint8_t* data, uint32_t data_length));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *write)(struct IDiscordStorageManager* manager, const char* name, uint8_t* data, uint32_t data_length);
	void (]] .. DISCORD_API .. [[ *write_async)(struct IDiscordStorageManager* manager, const char* name, uint8_t* data, uint32_t data_length, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *delete_)(struct IDiscordStorageManager* manager, const char* name);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *exists)(struct IDiscordStorageManager* manager, const char* name, bool* exists);
	void (]] .. DISCORD_API .. [[ *count)(struct IDiscordStorageManager* manager, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *stat)(struct IDiscordStorageManager* manager, const char* name, struct DiscordFileStat* stat);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *stat_at)(struct IDiscordStorageManager* manager, int32_t index, struct DiscordFileStat* stat);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_path)(struct IDiscordStorageManager* manager, DiscordPath* path);
};

struct IDiscordStoreEvents {
	void (]] .. DISCORD_API .. [[ *on_entitlement_create)(void* event_data, struct DiscordEntitlement* entitlement);
	void (]] .. DISCORD_API .. [[ *on_entitlement_delete)(void* event_data, struct DiscordEntitlement* entitlement);
};
]],
[[
struct IDiscordStoreManager {
	void (]] .. DISCORD_API .. [[ *fetch_skus)(struct IDiscordStoreManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *count_skus)(struct IDiscordStoreManager* manager, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_sku)(struct IDiscordStoreManager* manager, DiscordSnowflake sku_id, struct DiscordSku* sku);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_sku_at)(struct IDiscordStoreManager* manager, int32_t index, struct DiscordSku* sku);
	void (]] .. DISCORD_API .. [[ *fetch_entitlements)(struct IDiscordStoreManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *count_entitlements)(struct IDiscordStoreManager* manager, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_entitlement)(struct IDiscordStoreManager* manager, DiscordSnowflake entitlement_id, struct DiscordEntitlement* entitlement);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_entitlement_at)(struct IDiscordStoreManager* manager, int32_t index, struct DiscordEntitlement* entitlement);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *has_sku_entitlement)(struct IDiscordStoreManager* manager, DiscordSnowflake sku_id, bool* has_entitlement);
	void (]] .. DISCORD_API .. [[ *start_purchase)(struct IDiscordStoreManager* manager, DiscordSnowflake sku_id, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
};

struct IDiscordVoiceEvents {
	void (]] .. DISCORD_API .. [[ *on_settings_update)(void* event_data);
};

struct IDiscordVoiceManager {
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_input_mode)(struct IDiscordVoiceManager* manager, struct DiscordInputMode* input_mode);
	void (]] .. DISCORD_API .. [[ *set_input_mode)(struct IDiscordVoiceManager* manager, struct DiscordInputMode input_mode, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	enum EDiscordResult (]] .. DISCORD_API .. [[ *is_self_mute)(struct IDiscordVoiceManager* manager, bool* mute);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_self_mute)(struct IDiscordVoiceManager* manager, bool mute);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *is_self_deaf)(struct IDiscordVoiceManager* manager, bool* deaf);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_self_deaf)(struct IDiscordVoiceManager* manager, bool deaf);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *is_local_mute)(struct IDiscordVoiceManager* manager, DiscordSnowflake user_id, bool* mute);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_local_mute)(struct IDiscordVoiceManager* manager, DiscordSnowflake user_id, bool mute);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_local_volume)(struct IDiscordVoiceManager* manager, DiscordSnowflake user_id, uint8_t* volume);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *set_local_volume)(struct IDiscordVoiceManager* manager, DiscordSnowflake user_id, uint8_t volume);
};

struct IDiscordAchievementEvents {
	void (]] .. DISCORD_API .. [[ *on_user_achievement_update)(void* event_data, struct DiscordUserAchievement* user_achievement);
};

struct IDiscordAchievementManager {
	void (]] .. DISCORD_API .. [[ *set_user_achievement)(struct IDiscordAchievementManager* manager, DiscordSnowflake achievement_id, uint8_t percent_complete, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *fetch_user_achievements)(struct IDiscordAchievementManager* manager, void* callback_data, void (]] .. DISCORD_API .. [[ *callback)(void* callback_data, enum EDiscordResult result));
	void (]] .. DISCORD_API .. [[ *count_user_achievements)(struct IDiscordAchievementManager* manager, int32_t* count);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_user_achievement)(struct IDiscordAchievementManager* manager, DiscordSnowflake user_achievement_id, struct DiscordUserAchievement* user_achievement);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *get_user_achievement_at)(struct IDiscordAchievementManager* manager, int32_t index, struct DiscordUserAchievement* user_achievement);
};

typedef void* IDiscordCoreEvents;

struct IDiscordCore {
	void (]] .. DISCORD_API .. [[ *destroy)(struct IDiscordCore* core);
	enum EDiscordResult (]] .. DISCORD_API .. [[ *run_callbacks)(struct IDiscordCore* core);
	void (]] .. DISCORD_API .. [[ *set_log_hook)(struct IDiscordCore* core, enum EDiscordLogLevel min_level, void* hook_data, void (]] .. DISCORD_API .. [[ *hook)(void* hook_data, enum EDiscordLogLevel level, const char* message));
	struct IDiscordApplicationManager* (]] .. DISCORD_API .. [[ *get_application_manager)(struct IDiscordCore* core);
	struct IDiscordUserManager* (]] .. DISCORD_API .. [[ *get_user_manager)(struct IDiscordCore* core);
	struct IDiscordImageManager* (]] .. DISCORD_API .. [[ *get_image_manager)(struct IDiscordCore* core);
	struct IDiscordActivityManager* (]] .. DISCORD_API .. [[ *get_activity_manager)(struct IDiscordCore* core);
	struct IDiscordRelationshipManager* (]] .. DISCORD_API .. [[ *get_relationship_manager)(struct IDiscordCore* core);
	struct IDiscordLobbyManager* (]] .. DISCORD_API .. [[ *get_lobby_manager)(struct IDiscordCore* core);
	struct IDiscordNetworkManager* (]] .. DISCORD_API .. [[ *get_network_manager)(struct IDiscordCore* core);
	struct IDiscordOverlayManager* (]] .. DISCORD_API .. [[ *get_overlay_manager)(struct IDiscordCore* core);
	struct IDiscordStorageManager* (]] .. DISCORD_API .. [[ *get_storage_manager)(struct IDiscordCore* core);
	struct IDiscordStoreManager* (]] .. DISCORD_API .. [[ *get_store_manager)(struct IDiscordCore* core);
	struct IDiscordVoiceManager* (]] .. DISCORD_API .. [[ *get_voice_manager)(struct IDiscordCore* core);
	struct IDiscordAchievementManager* (]] .. DISCORD_API .. [[ *get_achievement_manager)(struct IDiscordCore* core);
};

struct DiscordCreateParams {
	DiscordClientId client_id;
	uint64_t flags;
	IDiscordCoreEvents* events;
	void* event_data;
	IDiscordApplicationEvents* application_events;
	DiscordVersion application_version;
	struct IDiscordUserEvents* user_events;
	DiscordVersion user_version;
	IDiscordImageEvents* image_events;
	DiscordVersion image_version;
	struct IDiscordActivityEvents* activity_events;
	DiscordVersion activity_version;
	struct IDiscordRelationshipEvents* relationship_events;
	DiscordVersion relationship_version;
	struct IDiscordLobbyEvents* lobby_events;
	DiscordVersion lobby_version;
	struct IDiscordNetworkEvents* network_events;
	DiscordVersion network_version;
	struct IDiscordOverlayEvents* overlay_events;
	DiscordVersion overlay_version;
	IDiscordStorageEvents* storage_events;
	DiscordVersion storage_version;
	struct IDiscordStoreEvents* store_events;
	DiscordVersion store_version;
	struct IDiscordVoiceEvents* voice_events;
	DiscordVersion voice_version;
	struct IDiscordAchievementEvents* achievement_events;
	DiscordVersion achievement_version;
};

static void* DiscordCreateParamsSetDefault(struct DiscordCreateParams* params);

enum EDiscordResult ]] .. DISCORD_API .. [[  DiscordCreate(DiscordVersion version, struct DiscordCreateParams* params, struct IDiscordCore** result);

typedef void (]] .. DISCORD_API .. [[ *callbackPtr)(void* callback_data, enum EDiscordResult result);

typedef void (]] .. DISCORD_API .. [[ *loggerPtr)(void* hook_data, enum EDiscordLogLevel level, const char* message);

typedef void (]] .. DISCORD_API .. [[ *onUserUpdatedPtr)(void* data);

typedef void (]] .. DISCORD_API .. [[ *onOAuth2Ptr)(void* data, enum EDiscordResult result, struct DiscordOAuth2Token* token);

struct Application {
	struct IDiscordCore* core;
	struct IDiscordUserManager* users;
	struct IDiscordAchievementManager* achievements;
	struct IDiscordActivityManager* activities;
	struct IDiscordRelationshipManager* relationships;
	struct IDiscordApplicationManager* application;
	struct IDiscordLobbyManager* lobbies;
	DiscordUserId user_id;
};
]]
}

-- Need to break down the string in smaller chunks
-- since it causes a "Chunk has too many syntax levels" error otherwise
-- https://help.interfaceware.com/v6/chunk-has-too-many-syntax-levels-error-very-large-string
ffi.cdef(table.concat(discord_game_sdk_h))

-- Implement set default function in Lua because
-- somehow I couldn't get FFI to call the static method
-- DiscordCreateParamsSetDefault
local function create_params_set_default(params_ptr)
	params_ptr[0].application_version = game_sdk.DISCORD_APPLICATION_MANAGER_VERSION
	params_ptr[0].user_version = game_sdk.DISCORD_USER_MANAGER_VERSION
	params_ptr[0].image_version = game_sdk.DISCORD_IMAGE_MANAGER_VERSION
	params_ptr[0].activity_version = game_sdk.DISCORD_ACTIVITY_MANAGER_VERSION
	params_ptr[0].relationship_version = game_sdk.DISCORD_RELATIONSHIP_MANAGER_VERSION
	params_ptr[0].lobby_version = game_sdk.DISCORD_LOBBY_MANAGER_VERSION
	params_ptr[0].network_version = game_sdk.DISCORD_NETWORK_MANAGER_VERSION
	params_ptr[0].overlay_version = game_sdk.DISCORD_OVERLAY_MANAGER_VERSION
	params_ptr[0].storage_version = game_sdk.DISCORD_STORAGE_MANAGER_VERSION
	params_ptr[0].store_version = game_sdk.DISCORD_STORE_MANAGER_VERSION
	params_ptr[0].voice_version = game_sdk.DISCORD_VOICE_MANAGER_VERSION
	params_ptr[0].achievement_version = game_sdk.DISCORD_ACHIEVEMENT_MANAGER_VERSION
	return params
end

-- Module table
local discord_game_sdk = {
	-- Shouldn't be overwritten
	LOG_LEVEL_NONE = 0,
	LOG_LEVEL_ERROR = 1,
	LOG_LEVEL_WARNING = 2,
	LOG_LEVEL_INFO = 3,

	options = {
		-- Can be overwritten
		print = print,
		log_level = 2,
	}
}

-- Proxy to detect garbage collection of the module
discord_game_sdk.gc_dummy = newproxy(true)

local on_user_updated = ffi.cast("onUserUpdatedPtr", function(data)
	local app_ptr = ffi.cast("struct Application*", data)
	local app = app_ptr[0]
	local user = ffi.new("struct DiscordUser")
	local user_ptr = ffi.new("struct DiscordUser[1]", user)
	app.users.get_current_user(app.users, user_ptr)
	user = user_ptr[0]

	if discord_game_sdk.options.log_level >= discord_game_sdk.LOG_LEVEL_INFO then
		discord_game_sdk.print(string.format("Displaying Discord Status on user: %s#%s", ffi.string(user.username), ffi.string(user.discriminator)))
	end
end)

local logger_callback = ffi.cast("loggerPtr", function(data, level, message)
	if discord_game_sdk.options.log_level >= discord_game_sdk.LOG_LEVEL_ERROR then
		discord_game_sdk.print(string.format("Discord reported an error of severity %s: %s", tostring(level), ffi.string(message)))
	end
end)

-- Helper function to make sure the input is a given type
function check_arg(arg, arg_type, arg_name, func, maybe_nil)
	assert(
		(type(arg) == arg_type) or ((maybe_nil) and (arg == nil)),
		string.format("Argument \"%s\" to function \"%s\" has to be of type \"%s\"",
			arg_name,
			func,
			arg_type
		)
	)
end

-- Helper function to make sure the input is a string within length
function check_str_arg(arg, max_len, arg_name, func, maybe_nil)
	if max_len then
		assert(
			((type(arg) == "string") and (arg:len() <= max_len)) or ((maybe_nil) and (arg == nil)),
			string.format("Argument \"%s\" of function \"%s\" has to be of type string with maximum length %d",
				arg_name,
				func,
				max_len
			)
		)
	else
		check_arg(arg, "string", arg_name, func, true)
	end
end

-- Helper function to make sure the input is within a max int value
function check_int_arg(arg, max_bits, arg_name, func, maybe_nil)
	max_bits = math.min(max_bits or 32, 52) -- lua number (double) can only store integers < 2^53
	local max_val = 2 ^ (max_bits - 1) -- assuming signed integers, which, for now, are the only ones in use
	assert(
		((type(arg) == "number") and (math.floor(arg) == arg) and (arg < max_val) and (arg >= -max_val)) or ((maxbe_nil) and (arg == nil)),
		string.format("Argument \"%s\" of function \"%s\" has to be a whole number <= %d",
			arg_name,
			func,
			max_val
		)
	)
end

-- This function is basically a complete line by line port
-- from examples/c/main.c in the Game SDK. with Lua quirks
-- here and there.

-- Pass by reference kinda works but kinda doesn't, and
-- so user_events != user_event_ptr[0], and app != app_ptr[0].
-- The desired one is always [0], so we simply do not use
-- the original objects after a pointer to them have been made.
function discord_game_sdk.initialize(client_id)
	local app = ffi.new("struct Application")
	local app_ptr = ffi.new("struct Application[1]", app)
	ffi.C.memset(app_ptr, 0, ffi.sizeof(app))

	local user_events = ffi.new("struct IDiscordUserEvents")
	local user_event_ptr = ffi.new("struct IDiscordUserEvents[1]", user_events)
	ffi.C.memset(user_event_ptr, 0, ffi.sizeof(user_events))

	user_event_ptr[0].on_current_user_update = on_user_updated

	local params = ffi.new("struct DiscordCreateParams")
	local params_ptr = ffi.new("struct DiscordCreateParams[1]", params)
	ffi.C.memset(params_ptr, 0, ffi.sizeof(params))
	create_params_set_default(params_ptr)
	params_ptr[0].client_id = client_id
	params_ptr[0].flags = game_sdk.DiscordCreateFlags_NoRequireDiscord
	params_ptr[0].event_data = app_ptr
	params_ptr[0].user_events = user_event_ptr

	local core_ptr_ptr = ffi.new("struct IDiscordCore*[1]", app.core)
	ffi.C.memset(core_ptr_ptr, 0, ffi.sizeof(app.core))

	-- Attempt to create a Discord instance
	local result = game_sdk.DiscordCreate(game_sdk.DISCORD_VERSION, params_ptr, core_ptr_ptr)
	local running = (result == game_sdk.DiscordResult_Ok)

	if running then
		app_ptr[0].core = core_ptr_ptr[0]

		app_ptr[0].core:set_log_hook(game_sdk.DiscordLogLevel_Debug, app_ptr, logger_callback)

		app_ptr[0].activities = app_ptr[0].core[0]:get_activity_manager()
		app_ptr[0].application = app_ptr[0].core[0]:get_application_manager()
		app_ptr[0].users = app_ptr[0].core[0]:get_user_manager()

		discord_game_sdk.run_callbacks(app_ptr[0].core)
	end

	-- By http://lua-users.org/lists/lua-l/2011-04/msg00516.html,
	-- The LuaJIT FFI Garbage Collector doesn't follow pointers when
	-- determining which references to keep. Therefore, "you must
	-- not store the only reference to an object allocated with
	-- ffi.new() as a pointer in a struct field."
	-- Hence, a references_table is passed around instead of just
	-- the app, although none of the keys are used apart from app.
	local references_table = {
		running = running,
		client_id = client_id,
		app = app_ptr[0],
		app_ptr = app_ptr,
		userEvents = userEvents,
		user_event_ptr = user_event_ptr,
		corePtr = app_ptr[0].core,
		core_ptr_ptr = core_ptr_ptr,
		activities = app_ptr[0].activities,
		application = app_ptr[0].application,
		users = app_ptr[0].users
	}

	-- Prevent memory leak when called multiple times by explicitly
	-- calling the garbage collector (twice, because some SO user said so)
	collectgarbage()
	collectgarbage()

	return references_table
end

function discord_game_sdk.shutdown(app)
	app.core:destroy()
end

function discord_game_sdk.run_callbacks(core)
	return core.run_callbacks(core)
end

local update_activity_callback = ffi.cast("callbackPtr", function(callback_data, discord_result)
	if discord_result == game_sdk.DiscordResult_Ok then
		if discord_game_sdk.options.log_level >= discord_game_sdk.LOG_LEVEL_INFO then
			discord_game_sdk.print("Successfully updated Discord activity")
		end
	else
		if discord_game_sdk.options.log_level >= discord_game_sdk.LOG_LEVEL_WARNING then
			discord_game_sdk.print(string.format("Failed updating Discord activity: %s", tostring(discord_result)))
		end
	end
end)

local clear_activity_callback = ffi.cast("callbackPtr", function(callback_data, discord_result)
	if discord_result == game_sdk.DiscordResult_Ok then
		if discord_game_sdk.options.log_level >= discord_game_sdk.LOG_LEVEL_INFO then
			discord_game_sdk.print("Successfully cleared Discord activity")
		end
	else
		if discord_game_sdk.options.log_level >= discord_game_sdk.LOG_LEVEL_WARNING then
			discord_game_sdk.print(string.format("Failed clearing Discord activity: %s", tostring(discord_result)))
		end
	end
end)

function discord_game_sdk.update_presence(references_table, presence)
	-- If Discord isn't running, try initialising.
	-- If it still fails, then return early.
	if not references_table.running then
		references_table = discord_game_sdk.initialize(references_table.client_id)
		if not references_table.running then
			return references_table
		end
	end

	local func = "discord_game_sdk.update_presence"

	check_arg(presence, "table", "presence", func)

	-- -- -1 for string length because of 0-termination
	check_str_arg(presence.state, 127, "presence.state", func, true)
	check_str_arg(presence.details, 127, "presence.details", func, true)

	check_int_arg(presence.start_time, 64, "presence.start_time", func, true)
	check_int_arg(presence.end_time, 64, "presence.end_time", func, true)

	check_str_arg(presence.large_image, 127, "presence.large_image", func, true)
	check_str_arg(presence.large_text, 127, "presence.large_text", func, true)
	check_str_arg(presence.small_image, 127, "presence.small_image", func, true)
	check_str_arg(presence.small_text, 127, "presence.small_text", func, true)

	check_str_arg(presence.party_id, 127, "presence.party_id", func, true)
	check_int_arg(presence.party_size, 32, "presence.party_size", func, true)
	check_int_arg(presence.party_max, 32, "presence.party_max", func, true)

	check_str_arg(presence.match_secret, 127, "presence.match_secret", func, true)
	check_str_arg(presence.join_secret, 127, "presence.join_secret", func, true)
	check_str_arg(presence.spectate_secret, 127, "presence.spectate_secret", func, true)

	local app = references_table.app
	app.activities = app.core[0]:get_activity_manager()
	app.application = app.core[0]:get_application_manager()
	app.users = app.core[0]:get_user_manager()

	local activity = ffi.new("struct DiscordActivity")
	local activity_ptr = ffi.new("struct DiscordActivity[1]", activity)
	ffi.C.memset(activity_ptr, 0, ffi.sizeof(activity))

	activity_ptr[0].type = game_sdk.DiscordActivityType_Playing
	activity_ptr[0].state = presence.state or ""
	activity_ptr[0].details = presence.details or ""
	activity_ptr[0].timestamps.start = presence.start_time or 0
	activity_ptr[0].timestamps["end"] = presence.end_time or 0
	activity_ptr[0].assets.large_image = presence.large_image or ""
	activity_ptr[0].assets.large_text = presence.large_text or ""
	activity_ptr[0].assets.small_image = presence.small_image or ""
	activity_ptr[0].assets.small_text = presence.small_text or ""
	activity_ptr[0].party.id = presence.party_id or ""
	activity_ptr[0].party.size.current_size = presence.party_size or 0
	activity_ptr[0].party.size.max_size = presence.party_max or 0
	activity_ptr[0].secrets.match = presence.match_secret or ""
	activity_ptr[0].secrets.join = presence.join_secret or ""
	activity_ptr[0].secrets.spectate = presence.spectate_secret or ""

	app.activities:update_activity(activity_ptr, app.core, update_activity_callback)
	local result = discord_game_sdk.run_callbacks(app.core)
	local running = (result == game_sdk.DiscordResult_Ok)

	-- Make sure garbage memory is collected, or otherwise
	-- this script will keep on increasming RAM usage by about 8KB
	-- everytime updateActivity or clearActivity is run.
	collectgarbage()
	collectgarbage()

	references_table.running = running
	return references_table
end

function discord_game_sdk.clear_presence(references_table)
	-- If Discord isn't running, don't even try.
	if not references_table.running then
		return references_table
	end

	local app = references_table.app
	app.activities = app.core[0]:get_activity_manager()
	app.application = app.core[0]:get_application_manager()
	app.users = app.core[0]:get_user_manager()

	app.activities:clear_activity(app.core, clear_activity_callback)
	local result = discord_game_sdk.run_callbacks(app.core)
	local running = (result == game_sdk.DiscordResult_Ok)

	collectgarbage()
	collectgarbage()

	references_table.running = running
	return references_table
end

-- Attach a finaliser to run when discord_game_sdk is garbage
-- collected. This happens when mpv quits.
getmetatable(discord_game_sdk.gc_dummy).__gc = function ()
	discord_game_sdk.shutdown()
	update_activity_callback:free()
	clear_activity_callback:free()
	logger_callback:free()
end

-- http://luajit.org/ext_ffi_semantics.html#callback :
-- It is by default not allowed for C to callback into Lua, when
-- Lua had originally called into C. jit.off() allows it, so any
-- function that calls a callback needs to be wrapped in it.
jit.off(discord_game_sdk.update_presence)
jit.off(discord_game_sdk.clear_presence)
jit.off(discord_game_sdk.run_callbacks)
jit.off(discord_game_sdk.initialize)

return discord_game_sdk
