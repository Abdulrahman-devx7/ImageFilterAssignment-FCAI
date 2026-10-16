#pragma once
#include "Image_Class.h"
#include <string>

struct Node
{
    Node *prev;
    Image image;
    std::string imageName;
    Node *next;
    Node(Node *back = nullptr, const Image& image = Image(), const std::string& imageName = "", Node *forward = nullptr)
    {
        this->prev = back;
        this->image = image;
        this->imageName = imageName;
        this->next = forward;
    }
};

class ImageHistory
{
    Node *head;
    Node *current;

    void delete_forward()
    {
        if (!current) return;
        Node *del = current->next;
        Node *ref = del;
        while (del)
        {
            ref = ref->next;
            delete del;
            del = ref;
        }
        current->next = nullptr;
    }

public:
    ImageHistory(const Image& image, const std::string& imageName = "")
    {
        head = new Node(nullptr, image, imageName);
        current = head;
    }

    ~ImageHistory()
    {
        clear();
    }

    void clear()
    {
        current = head;
        while (head)
        {
            current = current->next;
            delete head;
            head = current;
        }
        head = nullptr;
        current = nullptr;
    }

    void newImage(const Image& image, const std::string& imageName = "")
    {
        if (!current) {
            head = new Node(nullptr, image, imageName);
            current = head;
            return;
        }

        delete_forward();
        Node *new_node = new Node(current, image, imageName);
        current->next = new_node;
        current = current->next;
    }

    Node backward(int steps = 1)
    {
        for (int i = 0; current && current->prev && i < steps; i++)
            current = current->prev;
        return current ? *current : Node();
    }

    Node forward(int steps = 1)
    {
        for (int i = 0; current && current->next && i < steps; i++)
            current = current->next;
        return current ? *current : Node();
    }

    bool canBackward() const
    {
        return current != nullptr && current->prev != nullptr;
    }

    bool canForward() const
    {
        return current != nullptr && current->next != nullptr;
    }

    Node* getCurrentNode() const
    {
        return current;
    }

    Node* getHeadNode() const
    {
        return head;
    }

    int getUndoCount() const
    {
        int count = 0;
        Node* p = current;
        while (p && p->prev) {
            count++;
            p = p->prev;
        }
        return count;
    }

    int getRedoCount() const
    {
        int count = 0;
        Node* p = current;
        while (p && p->next) {
            count++;
            p = p->next;
        }
        return count;
    }

    int getTotalCount() const
    {
        return getUndoCount() + getRedoCount() + (current != nullptr ? 1 : 0);
    }

    int getCurrentIndex() const
    {
        return getUndoCount() + (current != nullptr ? 1 : 0);
    }
};
