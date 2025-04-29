package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Posting extends AbstractPosting {
    public Posting() {
        this.docId = -1;
        this.freq = 0;
        this.positions = new ArrayList<>();
    }
    public Posting(int docId, int freq, List<Integer> positions) {
        this.docId = docId;
        this.freq = freq;
        this.positions = positions;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj) return true;
        if(obj.getClass() != this.getClass()) return false;
        Posting posting = (Posting) obj;
        return this.docId == posting.docId && this.freq == posting.freq && this.positions.size()==posting.positions.size() && this.positions.containsAll(posting.positions) ;
    }

    @Override
    public String toString() {
        return "Posting( docId = " + docId + ", freq = " + freq + ", positions = " + positions + ")";
    }

    @Override
    public int getDocId() {
        return this.docId;
    }

    @Override
    public void setDocId(int docId) {
        this.docId = docId;
    }

    @Override
    public int getFreq() {
        return this.freq;
    }

    @Override
    public void setFreq(int freq) {
        this.freq = freq;
    }

    @Override
    public List<Integer> getPositions() {
        return this.positions;
    }

    @Override
    public void setPositions(List<Integer> positions) {
        this.positions = positions;
    }

    @Override
    public int compareTo(AbstractPosting o) {
        return this.docId - o.getDocId();
    }

    @Override
    public void sort() {
        this.positions.sort(Comparator.comparingInt(Integer::intValue));
    }

    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(this.docId);
            out.writeObject(this.freq);
            out.writeObject(this.positions);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void readObject(ObjectInputStream in) {
        try {
            this.docId = (int)in.readObject();
            this.freq = (int)in.readObject();
            this.positions = (List<Integer>)in.readObject();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
