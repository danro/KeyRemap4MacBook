#ifndef SIMULTANEOUSKEYPRESSES_HPP
#define SIMULTANEOUSKEYPRESSES_HPP

#include "RemapFuncBase.hpp"
#include "EventInputQueue.hpp"
#include "FromKeyChecker.hpp"
#include "KeyToKey.hpp"
#include "KeyToPointingButton.hpp"

namespace org_pqrs_KeyRemap4MacBook {
  namespace RemapFunc {
    class SimultaneousKeyPresses {
    public:
      enum Option {
        OPTION_RAW,
      };

      SimultaneousKeyPresses(void) : index_(0) {}
      void initialize(void);
      void terminate(void);
      void remap(void);
      bool handlevirtualkey(const Params_KeyboardEventCallBack& params);

      // ----------------------------------------
      // [0] => virtualkey
      // [1] => fromKey1_
      // [2] => fromKey2_
      // [3] => toKeys_[0]
      // [4] => toKeys_[1]
      // [5] => ...
      void add(KeyCode newval);
      void add(PointingButton newval);
      void add(Flags newval);
      void add(Option newval);

    private:
      void push_remapped(bool isKeyDown);

      class FromInfo {
      public:
        FromInfo(void) : active_(false) {}

        enum FromType {
          FROMTYPE_KEY,
          FROMTYPE_BUTTON,
        };
        void set(KeyCode k)        { type_ = FROMTYPE_KEY;    key_ = k; }
        void set(PointingButton b) { type_ = FROMTYPE_BUTTON; button_ = b; }
        void activate(void)        { active_ = true; }
        bool restore(bool isFireUp);

        EventInputQueue::Item* findLastItem(bool& isKeyDown, bool isIncludeDropped);

      private:
        FromType type_;
        KeyCode key_;
        PointingButton button_;
        bool active_;
      };

      // --------------------
      size_t index_;
      KeyCode virtualkey_;

      FromInfo fromInfo1_;
      FromInfo fromInfo2_;
      Flags fromFlags_;

      // --------------------
      enum ToType {
        TOTYPE_NONE,
        TOTYPE_KEY,
        TOTYPE_BUTTON,
      } toType_;

      bool isToRaw_;
      KeyCode toKey_raw_;

      KeyToKey keytokey_;
      KeyToPointingButton keytopointingbutton_;
    };
  }
}

#endif
