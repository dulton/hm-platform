/*
 * hm_list.c
 *
 * This file implements list.
 *
 * Copyright(c) by HiMickey, 2010~2014
 * Author:
*/

#include "hm_list.h"
#include "hm_mem.h"


JList *hm_list_alloc( void )
{
	JList *list = hm_new(JList, 1);
	return list;
}


JList *hm_list_add(JList *list, void *data)
{
	JList *new_list = hm_list_alloc();

	new_list->data = data;
	new_list->next = list;
	new_list->prev = NULL;

	if (list)
		list->prev = new_list;

	return new_list;
}


JList *hm_list_add_tail(JList *list, void *data)
{
	JList *new_list = hm_list_alloc();
	JList *last;

	new_list->data = data;
	new_list->next = NULL;

	if (list)
	{
		last = hm_list_last(list);
		new_list->prev = last;
		last->next = new_list;
		return list;
	}
	else
	{
		new_list->prev = NULL;
		return new_list;
	}
}


JList *hm_list_remove(JList *list, void *data)
{
	JList *head = list;

	while (list)
	{
		if (list->data != data)
			list = list->next;
		else
		{
			if (list->prev)
				list->prev->next = list->next;
			if (list->next)
				list->next->prev = list->prev;

			if (head == list)
				head = head->next;

			hm_list_free_1(list);
			break;
		}
	}

	return head;
}


JList *hm_list_remove_all(JList *list, void *data)
{
	JList *next, *head = list;

	while (list)
	{
		if (list->data != data)
			list = list->next;
		else
		{
			next = list->next;

			if (list->prev)
				list->prev->next = next;
			else
				head = next;

			if (next)
				next->prev = list->prev;

			hm_list_free_1(list);
			list = next;
		}
	}

	return head;	
}


JList *hm_list_remove_link(JList *list, JList *link)
{
	if (link)
	{
		if (link->next)
			link->next->prev = link->prev;
		if (link->prev)
			link->prev->next = link->next;

		if (link == list)
			list = list->next;

		link->next = NULL;
		link->prev = NULL;
	}

	return list;
}


JList *hm_list_delete_link(JList *list, JList *link)
{
	list = hm_list_remove_link(list, link);
	hm_list_free_1(link);

	return list;
}


JList *hm_list_concat(JList *list1, JList *list2)
{
	JList *last;

	if (list2)
	{
		last = hm_list_last(list1);
		if (last)
			last->next = list2;
		else
			list1 = list2;
		list2->prev = last;
	}

	return list1;	
}


JList *hm_list_find(JList *list, void *data)
{
	while (list)
	{
		if (list->data == data)
			break;
		list = list->next;
	}

	return list;
}


JList *hm_list_find_custom(JList *list, void *data,
	JCompareCustom func)
{
	while (list)
	{
		if (!(*func)(list->data, data))
			break;
		list = list->next;
	}

	return list;
}


void hm_list_foreach(JList *list, JVisitCustom func, void *data)
{
	JList *next;

	while (list)
	{
		next = list->next;
		(*func)(list->data, data);
		list = next;
	}
}


void hm_list_free_1(JList *list)
{
	if (list)
		hm_del(list, JList, 1);
}


void hm_list_free(JList *list)
{
	JList *next;

	while (list)
	{
		next = list->next;
		hm_list_free_1(list);
		list = next;
	}
}



JList *hm_list_first(JList *list)
{
	if (list)
	{
		while (list->prev)
			list = list->prev;
	}

	return list;
}


JList *hm_list_last(JList *list)
{
	if (list)
	{
		while (list->next)
			list = list->next;
	}

	return list;
}


//: ~End
