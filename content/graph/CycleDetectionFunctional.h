/**
 * Author: Unknown
 * Date: 2024-01-01
 * License: CC0
 * Source: own work
 * Description: Floyd's tortoise and hare algorithm for cycle detection in a functional graph (e.g., linked list).
 * Time: O(N)
 * Status: tested
 */
#pragma once

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool hasCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

ListNode* findCycleStart(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;
    bool has_cycle = false;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            has_cycle = true;
            break;
        }
    }
    if (!has_cycle) return nullptr;
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
