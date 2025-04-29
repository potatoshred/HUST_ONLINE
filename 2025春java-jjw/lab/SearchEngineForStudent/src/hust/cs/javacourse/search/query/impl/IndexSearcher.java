package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;

import java.io.File;
import java.util.*;

public class IndexSearcher extends AbstractIndexSearcher {
    @Override
    public void open(String indexFile) {
        this.index.load(new File(indexFile));
    }

    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        AbstractPostingList postingList = index.search(queryTerm);
        if (postingList == null) {
            return null;
        }
        List<AbstractHit> hits = new ArrayList<>();
        AbstractPosting posting;
        int length = postingList.size();
        for (int i = 0; i < length; i++) {
            posting = postingList.get(i);
            HashMap<AbstractTerm, AbstractPosting> newMap = new HashMap<>();
            newMap.put(queryTerm, posting);
            AbstractHit newHit = new Hit(posting.getDocId(), index.getDocName(posting.getDocId()), newMap);
            newHit.setScore(sorter.score(newHit));
            hits.add(newHit);
        }
        sorter.sort(hits);

        return hits.toArray(new AbstractHit[hits.size()]);
    }

    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine) {
        // queryTerm2 = new Term(queryTerm2.toString().toLowerCase());
        // queryTerm1 = new Term(queryTerm1.toString().toLowerCase());
        AbstractPostingList postingList1 = index.search(queryTerm1);
        AbstractPostingList postingList2 = index.search(queryTerm2);
        int length1 = postingList1.size();
        int length2 = postingList2.size();

        List<AbstractHit> hits = new ArrayList<>();
        AbstractPosting posting;
        AbstractPosting posting1;
        AbstractPosting posting2;

        if (combine==LogicalCombination.OR){
            if (postingList1 == null && postingList2 == null) return new AbstractHit[0];
            int i=0,j=0;
            while (i < length1 && j < length2) {
                posting1 = postingList1.get(i);
                posting2 = postingList2.get(j);
                Map<AbstractTerm,AbstractPosting> newMap=new HashMap<>();

                if (posting1.getDocId() < posting2.getDocId()) {
                    posting = posting1;
                    newMap.put(queryTerm1, posting1);
                    i++;
                } else if (posting1.getDocId() > posting2.getDocId()) {
                    posting = posting2;
                    newMap.put(queryTerm2, posting2);
                    j++;
                }else {
                    posting = posting1;
                    newMap.put(queryTerm1, posting1);
                    newMap.put(queryTerm2, posting2);
                    i++;
                    j++;
                }
                AbstractHit newHit = new Hit(posting.getDocId(), index.getDocName(posting.getDocId()), newMap);
                newHit.setScore(sorter.score(newHit));
                hits.add(newHit);
            }

            while (i < length1 ) {
                posting1 = postingList1.get(i);
                Map<AbstractTerm,AbstractPosting> newMap=new HashMap<>();
                newMap.put(queryTerm1, posting1);
                AbstractHit newHit = new Hit(posting1.getDocId(), index.getDocName(posting1.getDocId()), newMap);
                newHit.setScore(sorter.score(newHit));
                hits.add(newHit);
                i++;
            }

            while (j < length2 ) {
                posting2 = postingList2.get(j);
                Map<AbstractTerm,AbstractPosting> newMap=new HashMap<>();
                newMap.put(queryTerm2, posting2);
                AbstractHit newHit = new Hit(posting2.getDocId(), index.getDocName(posting2.getDocId()), newMap);
                newHit.setScore(sorter.score(newHit));
                hits.add(newHit);
                j++;
            }

        } else if (combine==LogicalCombination.AND) {
            if (postingList1 == null || postingList2 == null) return new AbstractHit[0];
            int i=0,j=0;
            while (i < length1 && j < length2) {
                posting1 = postingList1.get(i);
                posting2 = postingList2.get(j);
                Map<AbstractTerm,AbstractPosting> newMap=new HashMap<>();
                if (posting1.getDocId() < posting2.getDocId()) {
                    i++;
                } else if (posting1.getDocId()>posting2.getDocId()) {
                    j++;
                }else {
                    newMap.put(queryTerm1, posting1);
                    newMap.put(queryTerm2, posting2);
                    AbstractHit newHit = new Hit(posting1.getDocId(), index.getDocName(posting1.getDocId()), newMap);
                    newHit.setScore(sorter.score(newHit));
                    hits.add(newHit);
                    i++;
                    j++;
                }
            }
        }else if (combine==LogicalCombination.ADJACENT){
            if (postingList1 == null || postingList2 == null) return new AbstractHit[0];
            int i=0,j=0;
            while (i < length1 && j < length2) {
                posting1 = postingList1.get(i);
                posting2 = postingList2.get(j);
                Map<AbstractTerm,AbstractPosting> newMap=new HashMap<>();
                if (posting1.getDocId() < posting2.getDocId()) {
                    i++;
                } else if (posting1.getDocId()>posting2.getDocId()) {
                    j++;
                }else {
                    List<Integer> positions1 = posting1.getPositions();
                    List<Integer> positions2 = posting2.getPositions();
                    int p1=0, p2=0, pos1, pos2;
                    while (p1 < positions1.size() && p2 < positions1.size()) {
                        pos1 = positions1.get(p1);
                        pos2 = positions2.get(p2);
                        if (pos1+1 < pos2) {
                            p1++;
                        }
                        else if (pos1+1>pos2) {
                            p2++;
                        }
                        else {
                            newMap.put(queryTerm1, posting1);
                            newMap.put(queryTerm2, posting2);
                            AbstractHit newHit = new Hit(posting1.getDocId(), index.getDocName(posting1.getDocId()), newMap);
                            newHit.setScore(sorter.score(newHit));
                            hits.add(newHit);
                            i++;
                            j++;
                            break;
                        }
                    }
                }
            }
        }


        sorter.sort(hits);
        return hits.toArray(new AbstractHit[0]);
    }
}
