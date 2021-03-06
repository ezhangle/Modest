/*
 Copyright (C) 2016 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#include "modest/finder/match.h"

bool modest_finder_match_attribute_only_key(myhtml_token_attr_t* attr, const char* key, size_t key_len)
{
    if(key == NULL)
        return false;
    
    while (attr)
    {
        if(attr->key.length == key_len) {
            if(myhtml_strncasecmp(key, attr->key.data, key_len) == 0)
                return true;
        }
        
        attr = attr->next;
    }
    
    return false;
}

bool modest_finder_match_attribute_eq(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive)
{
    if(key == NULL || value == NULL)
        return false;
    
    while (attr)
    {
        if(attr->key.length == key_len) {
            if(myhtml_strncasecmp(key, attr->key.data, key_len) == 0)
            {
                if(attr->value.length == value_len) {
                    if(case_sensitive) {
                        if(strncmp(value, attr->value.data, value_len) == 0) {
                            return true;
                        }
                    }
                    else {
                        if(myhtml_strncasecmp(value, attr->value.data, value_len) == 0) {
                            return true;
                        }
                    }
                }
                
                break;
            }
        }
        
        attr = attr->next;
    }
    
    return false;
}

bool modest_finder_match_attribute_ws(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive)
{
    if(key == NULL || value == NULL)
        return false;
    
    while (attr)
    {
        if(attr->key.length == key_len) {
            if(myhtml_strncasecmp(key, attr->key.data, key_len) == 0)
            {
                size_t i = 0;
                
                if(attr->value.length >= value_len) {
                    if(case_sensitive)
                    {
                        while(i < attr->value.length)
                        {
                            size_t end = i + value_len;
                            
                            if(end > attr->value.length)
                                return false;
                            
                            if(
                               (myhtml_strncmp(value, &attr->value.data[i], value_len) == 0) &&
                               (myhtml_utils_whithspace(attr->value.data[end], ==, ||) || end == attr->value.length))
                            {
                                return true;
                            }
                            
                            i++;
                        }
                    }
                    else {
                        while(i < attr->value.length)
                        {
                            size_t end = i + value_len;
                            
                            if(end > attr->value.length)
                                return false;
                            
                            if(
                               (myhtml_strncasecmp(value, &attr->value.data[i], value_len) == 0) &&
                               (myhtml_utils_whithspace(attr->value.data[end], ==, ||) || end == attr->value.length))
                            {
                                return true;
                            }
                            
                            i++;
                        }
                    }
                }
                
                break;
            }
        }
        
        attr = attr->next;
    }
    
    return false;
}

bool modest_finder_match_attribute_begin(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive)
{
    if(key == NULL || value == NULL)
        return false;
    
    while (attr)
    {
        if(attr->key.length == key_len) {
            if(myhtml_strncasecmp(key, attr->key.data, key_len) == 0)
            {
                if(attr->value.length >= value_len) {
                    if(case_sensitive) {
                        if(myhtml_strncmp(value, attr->value.data, value_len) == 0)
                            return true;
                    }
                    else {
                        if(myhtml_strncasecmp(value, attr->value.data, value_len) == 0)
                            return true;
                    }
                }
                
                break;
            }
        }
        
        attr = attr->next;
    }
    
    return false;
}

bool modest_finder_match_attribute_end(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive)
{
    if(key == NULL || value == NULL)
        return false;
    
    while (attr)
    {
        if(attr->key.length == key_len) {
            if(myhtml_strncasecmp(key, attr->key.data, key_len) == 0)
            {
                if(attr->value.length >= value_len) {
                    if(case_sensitive) {
                        if(myhtml_strncmp(value, &attr->value.data[ (attr->value.length - value_len) ], value_len) == 0)
                            return true;
                    }
                    else {
                        if(myhtml_strncasecmp(value, &attr->value.data[ (attr->value.length - value_len) ], value_len) == 0)
                            return true;
                    }
                }
                
                break;
            }
        }
        
        attr = attr->next;
    }
    
    return false;
}

bool modest_finder_match_attribute_sub(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive)
{
    if(key == NULL || value == NULL)
        return false;
    
    while (attr)
    {
        if(attr->key.length == key_len) {
            if(myhtml_strncasecmp(key, attr->key.data, key_len) == 0)
            {
                if(attr->value.length >= value_len) {
                    size_t i = 0;
                    
                    if(case_sensitive)
                    {
                        while ((i + value_len) <= attr->value.length)
                        {
                            if(myhtml_strncmp(value, &attr->value.data[i], value_len) == 0)
                                return true;
                            
                            i++;
                        }
                    }
                    else {
                        while ((i + value_len) <= attr->value.length)
                        {
                            if(myhtml_strncasecmp(value, &attr->value.data[i], value_len) == 0)
                                return true;
                            
                            i++;
                        }
                    }
                }
                
                break;
            }
        }
        
        attr = attr->next;
    }
    
    return false;
}

bool modest_finder_match_attribute_hsp(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive)
{
    if(key == NULL || value == NULL)
        return false;
    
    while (attr)
    {
        if(attr->key.length == key_len) {
            if(myhtml_strncasecmp(key, attr->key.data, key_len) == 0)
            {
                if(attr->value.length == value_len) {
                    if(case_sensitive) {
                        if(myhtml_strncmp(value, attr->value.data, value_len) == 0)
                            return true;
                    }
                    else {
                        if(myhtml_strncasecmp(value, attr->value.data, value_len) == 0)
                            return true;
                    }
                }
                else if(attr->value.length > value_len) {
                    if(case_sensitive) {
                        if(myhtml_strncmp(value, attr->value.data, value_len) == 0) {
                            if(attr->value.data[value_len] == '-')
                                return true;
                        }
                    }
                    else {
                        if(myhtml_strncasecmp(value, attr->value.data, value_len) == 0) {
                            if(attr->value.data[value_len] == '-')
                                return true;
                        }
                    }
                }
                
                break;
            }
        }
        
        attr = attr->next;
    }
    
    return false;
}


