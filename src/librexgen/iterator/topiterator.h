/*
    rexgen - a tool to create words based on regular expressions    
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin St, Fifth Floor, Boston, MA 02110, USA
 */


#ifndef TOPITERATOR_H
#define TOPITERATOR_H

#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/simplestring.h>


class TopIterator : public Iterator
{
public:
  TopIterator(int __id, Iterator* __child, IteratorState* __state)
    :Iterator(__id), child(__child), state(__state) {
  }
  
  ~TopIterator() {
    delete child;
    if (state->getStreamIterator() != nullptr) {
      delete (state->getStreamIterator());
    }
  }
  bool next() {
    bool res = child->next();
    if (res) { return res; }
    
    if (state->getStreamIterator() == nullptr) { return false; }
    return state->getStreamIterator()->forceNext();
  }
  
  void value(SimpleString& dst) const { child->value(dst); }
  bool hasNext() const { return child->hasNext(); }
  void updateReferences(IteratorState* iterState) {
        child->updateReferences(iterState);
  }
private:
  Iterator* child;
  const IteratorState* state;
};

#endif // TOPITERATOR_H
