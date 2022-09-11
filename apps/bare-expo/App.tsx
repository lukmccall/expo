import React from 'react';
import { View, Text, Button } from 'react-native';

const hashCode = function (s) {
  return s.split('').reduce(function (a, b) {
    a = (a << 5) - a + b.charCodeAt(0);
    return a & a;
  }, 0);
};

const Y = (function () {
  const _f = function _f() {
    return (
      <View>
        <Text>Shared Component</Text>
      </View>
    );
  };

  _f._string = `return function Y(){return/*#__PURE__*/React.createElement(jsThis.View,null,/*#__PURE__*/React.createElement(jsThis.Text,null,"Hi from Y!"));}`;
  _f._uiClosure = ['View', 'Text'];

  _f._name = 'Y';
  _f._fileName = 'App.tsx';
  _f._lineNumber = 4;
  _f._hash = '' + hashCode(_f._string);

  global.SharedUIEntryPoint?.exportSharedUI(_f);
  return _f;
})();

const X = (function () {
  const _f = function _f() {
    const [state, setState] = React.useState(0);
    return (
      <View>
        <Text style={{ fontSize: 50 }}>Counter {state}</Text>
        <Button
          title="Press me"
          onPress={() => {
            setState(state + 1);
          }}
        />
      </View>
    );
  };

  // _f._string = `return function X(){return/*#__PURE__*/React.createElement(jsThis.View,null,/*#__PURE__*/React.createElement(jsThis.Y,null),/*#__PURE__*/React.createElement(jsThis.Button,{title:"Press meee",onClick:function onClick(){console.log("hi from on click");}}));}`;
  // _f._uiClosure = ['View', 'Y', 'Button'];

  _f._string = `var _interopRequireDefault=require("@babel/runtime/helpers/interopRequireDefault");var _slicedToArray2=_interopRequireDefault(require("@babel/runtime/helpers/slicedToArray")); return function X(){var _React$useState=React.useState(0),_React$useState2=(0,_slicedToArray2.default)(_React$useState,2),state=_React$useState2[0],setState=_React$useState2[1];return/*#__PURE__*/React.createElement(jsThis.View,null,/*#__PURE__*/React.createElement(jsThis.Text,{style:{ fontSize: 50 }},"Counter ",state),/*#__PURE__*/React.createElement(jsThis.Button,{title:"Press me",onPress:function onClick(){setState(state+1);}}));}`;
  _f._uiClosure = ['View', 'Text', 'Button'];

  _f._name = 'X';
  _f._fileName = 'App.tsx';
  _f._lineNumber = 4;
  _f._hash = '' + hashCode(_f._string);

  global.SharedUIEntryPoint?.exportSharedUI(_f);
  return _f;
})();

export default function Main() {
  return (
    <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
      <X />
    </View>
  );
}

// import MainNavigator, { optionalRequire } from './MainNavigator';
// import { createProxy, startAsync, addListener } from './relapse/client';

// let Notifications;
// try {
//   Notifications = require('expo-notifications');
// } catch {
//   // do nothing
// }

// const loadAssetsAsync =
//   optionalRequire(() => require('native-component-list/src/utilities/loadAssetsAsync')) ??
//   (async () => null);

// function useLoaded() {
//   const [isLoaded, setLoaded] = React.useState(false);
//   React.useEffect(() => {
//     let isMounted = true;
//     // @ts-ignore
//     loadAssetsAsync()
//       .then(() => {
//         if (isMounted) setLoaded(true);
//       })
//       .catch((e) => {
//         console.warn('Error loading assets: ' + e.message);
//         if (isMounted) setLoaded(true);
//       });
//     return () => {
//       isMounted = false;
//     };
//   }, []);
//   return isLoaded;
// }

// export default function Main() {
//   // @ts-ignore
//   if (global.DETOX) {
//     React.useEffect(() => {
//       addListener((data) => {
//         if (data.globals) {
//           for (const moduleName of data.globals) {
//             // @ts-ignore
//             global[moduleName] = createProxy(moduleName);
//           }
//         }
//       });

//       let stop;
//       startAsync().then((_stop) => (stop = _stop));

//       return () => stop && stop();
//     }, []);
//   }

//   React.useEffect(() => {
//     try {
//       const subscription = Notifications.addNotificationResponseReceivedListener(
//         ({ notification, actionIdentifier }) => {
//           console.info(
//             `User interacted with a notification (action = ${actionIdentifier}): ${JSON.stringify(
//               notification,
//               null,
//               2
//             )}`
//           );
//         }
//       );
//       return () => subscription?.remove();
//     } catch (e) {
//       console.debug('Could not have added a listener for received notification responses.', e);
//     }
//   }, []);

//   const isLoaded = useLoaded();

//   if (!isLoaded) {
//     return null;
//   }

//   return <MainNavigator />;
// }
