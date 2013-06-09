// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder
#ifndef _PARTY_H_
#define _PARTY_H_
#include "../common/mmo.h" // struct party
struct block_list;
struct map_session_data;
struct party;
struct item;

#include <stdarg.h>

#define PARTY_BOOKING_JOBS 6
#define PARTY_BOOKING_RESULTS 10

struct party_member_data {
	struct map_session_data *sd;
	unsigned int hp; //For HP,x,y refreshing.
	unsigned short x, y;
};

struct party_data {
	struct party party;
	struct party_member_data data[MAX_PARTY];
	uint8 itemc; //For item distribution, position of last picker in party
	unsigned short *instance;
	unsigned short instances;
	struct {
		unsigned monk : 1; //There's at least one monk in party?
		unsigned sg : 1;	//There's at least one Star Gladiator in party?
		unsigned snovice :1; //There's a Super Novice
		unsigned tk : 1; //There's a taekwon
	} state;
};

#ifndef PARTY_RECRUIT
struct party_booking_detail {
	short level;
    short mapid;
    short job[PARTY_BOOKING_JOBS];
};

struct party_booking_ad_info {
	unsigned long index;
	char charname[NAME_LENGTH];
	long expiretime;
	struct party_booking_detail p_detail;
};
#else
#define PB_NOTICE_LENGTH (36 + 1)
struct party_booking_detail {
	short level;
	char notice[PB_NOTICE_LENGTH];
};

struct party_booking_ad_info {
	unsigned long index;
	long expiretime;
	char charname[NAME_LENGTH];
	struct party_booking_detail p_detail;
};
#endif


int party_foreachsamemap(int (*func)(struct block_list *,va_list),struct map_session_data *sd,int range,...);

/*==========================================
 * Party Booking in KRO [Spiria]
 *------------------------------------------*/

/*=====================================
* Interface : party.h 
* Generated by HerculesInterfaceMaker
* created by Susu
*-------------------------------------*/
struct party_interface {

	/* funcs */
	
	void (*do_init_party) (void);
	void (*do_final_party) (void);
	struct party_data* (*search) (int party_id);
	struct party_data* (*searchname) (const char* str);
	int (*getmemberid) (struct party_data* p, struct map_session_data* sd);
	struct map_session_data* (*getavailablesd) (struct party_data *p);
	
	int (*create) (struct map_session_data *sd,char *name, int item, int item2);
	void (*created) (int account_id,int char_id,int fail,int party_id,char *name);
	int (*request_info) (int party_id, int char_id);
	int (*invite) (struct map_session_data *sd,struct map_session_data *tsd);
	void (*member_joined) (struct map_session_data *sd);
	int (*member_added) (int party_id,int account_id,int char_id,int flag);
	int (*leave) (struct map_session_data *sd);
	int (*removemember) (struct map_session_data *sd,int account_id,char *name);
	int (*member_withdraw) (int party_id,int account_id,int char_id);
	void (*reply_invite) (struct map_session_data *sd,int party_id,int flag);
	int (*recv_noinfo) (int party_id, int char_id);
	int (*recv_info) (struct party* sp, int char_id);
	int (*recv_movemap) (int party_id,int account_id,int char_id, unsigned short map,int online,int lv);
	int (*broken) (int party_id);
	int (*optionchanged) (int party_id,int account_id,int exp,int item,int flag);
	int (*changeoption) (struct map_session_data *sd,int exp,int item);
	bool (*changeleader) (struct map_session_data *sd, struct map_session_data *t_sd);
	void (*send_movemap) (struct map_session_data *sd);
	void (*send_levelup) (struct map_session_data *sd);
	int (*send_logout) (struct map_session_data *sd);
	int (*send_message) (struct map_session_data *sd,const char *mes,int len);
	int (*recv_message) (int party_id,int account_id,const char *mes,int len);
	int (*skill_check) (struct map_session_data *sd, int party_id, uint16 skill_id, uint16 skill_lv);
	int (*send_xy_clear) (struct party_data *p);
	int (*exp_share) (struct party_data *p,struct block_list *src,unsigned int base_exp,unsigned int job_exp,int zeny);
	int (*share_loot) (struct party_data* p, struct map_session_data* sd, struct item* item_data, int first_charid);
	int (*send_dot_remove) (struct map_session_data *sd);
	int (*sub_count) (struct block_list *bl, va_list ap);
#ifndef PARTY_RECRUIT
	void (*booking_register) (struct map_session_data *sd, short level, short mapid, short* job);
	void (*booking_update) (struct map_session_data *sd, short* job);
	void (*booking_search) (struct map_session_data *sd, short level, short mapid, short job, unsigned long lastindex, short resultcount);
#else
	void (*booking_register) (struct map_session_data *sd, short level, const char *notice);
	void (*booking_update) (struct map_session_data *sd, const char *notice);
	void (*booking_search) (struct map_session_data *sd, short level, short mapid, unsigned long lastindex, short resultcount);
#endif
	bool (*booking_delete) (struct map_session_data *sd);
} party_s;

struct party_interface *party;

void party_defaults(void);

#endif /* _PARTY_H_ */
