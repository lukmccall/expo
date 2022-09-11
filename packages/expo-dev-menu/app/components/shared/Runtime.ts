import * as React from 'react';

const interopRequireDefault = require('@babel/runtime/helpers/interopRequireDefault');
const slicedToArray = require('@babel/runtime/helpers/slicedToArray');

function myRequire(name) {
  switch (name) {
    case '@babel/runtime/helpers/interopRequireDefault':
      return interopRequireDefault;
    case '@babel/runtime/helpers/slicedToArray':
      return slicedToArray;
  }

  return null;
}

export function createJsThisFromContext(context) {
  return Object.fromEntries(context.map((child) => [child.name, child.Component]));
}

export function evaluateSharedComponent(body, jsThis) {
  return eval(body)(jsThis, React, myRequire);
}
