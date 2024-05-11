#include <iostream>
#include <vector>

using namespace std;

class PageTableEntry {
public:
    int frameNumber;
    bool validBit;

    PageTableEntry() : frameNumber(-1), validBit(false) {}
};

class PageTable {
private:
    int numPages;
    vector<PageTableEntry> table;

public:
    PageTable(int numPages) : numPages(numPages) {
        table.resize(numPages);
    }

    void mapPageToFrame(int pageNumber, int frameNumber) {
        if (pageNumber >= 0 && pageNumber < numPages) {
            table[pageNumber].frameNumber = frameNumber;
            table[pageNumber].validBit = true;
            cout << "Page " << pageNumber << " mapped to frame " << frameNumber << endl;
        } else {
            cout << "Page number out of range" << endl;
        }
    }

    void accessPage(int pageNumber) {
        if (pageNumber >= 0 && pageNumber < numPages) {
            if (table[pageNumber].validBit) {
                cout << "Accessing page " << pageNumber << ", mapped to frame " << table[pageNumber].frameNumber << endl;
            } else {
                cout << "Page " << pageNumber << " is not mapped to any frame" << endl;
            }
        } else {
            cout << "Page number out of range" << endl;
        }
    }
};

class MemoryManager {
private:
    int numFrames;
    vector<bool> freeFrames;

public:
    MemoryManager(int numFrames) : numFrames(numFrames) {
        freeFrames.resize(numFrames, true);
    }

    int allocateFrame() {
        for (int i = 0; i < numFrames; ++i) {
            if (freeFrames[i]) {
                freeFrames[i] = false;
                return i;
            }
        }
        cout << "No free frames available" << endl;
        return -1;
    }

    void deallocateFrame(int frameNumber) {
        if (frameNumber >= 0 && frameNumber < numFrames) {
            freeFrames[frameNumber] = true;
        } else {
            cout << "Frame number out of range" << endl;
        }
    }
};

int main() {
    int numPages = 16;
    int numFrames = 8;

    PageTable pageTable(numPages);
    MemoryManager memoryManager(numFrames);

    pageTable.mapPageToFrame(0, memoryManager.allocateFrame());
    pageTable.mapPageToFrame(1, memoryManager.allocateFrame());
    pageTable.mapPageToFrame(2, memoryManager.allocateFrame());

    pageTable.accessPage(0);
    pageTable.accessPage(1);
    pageTable.accessPage(2);
    pageTable.accessPage(3);

    memoryManager.deallocateFrame(1);
    pageTable.mapPageToFrame(3, memoryManager.allocateFrame());

    pageTable.accessPage(0);
    pageTable.accessPage(1);
    pageTable.accessPage(2);
    pageTable.accessPage(3);

    return 0;
}

