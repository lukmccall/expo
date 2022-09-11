import * as ReactNative from 'react-native';

import * as Runtime from './Runtime';

const { SharedUIRegistry } = global;

const cache = {};
const dependencies = {};

export async function getComponentData(componentName, rootComponent = componentName) {
  if (componentName in cache) {
    return cache[componentName];
  }

  const nativeResponse = SharedUIRegistry.getComponentData(componentName);
  if (!nativeResponse) {
    if (ReactNative[componentName]) {
      const data = {
        Component: ReactNative[componentName],
        hash: `React_${componentName}`,
        name: componentName,
        children: [],
      };

      cache[componentName] = data;
      return Promise.resolve(data);
    }

    throw Error(`Unknown component ${componentName}`);
  }

  const childrenData = await Promise.all(
    nativeResponse.children.map((child) => getComponentData(child, rootComponent))
  );

  const jsThis = Runtime.createJsThisFromContext(childrenData);

  const Component = Runtime.evaluateSharedComponent(nativeResponse.body, jsThis);

  if (!dependencies[rootComponent]) {
    dependencies[rootComponent] = [];
  }

  dependencies[rootComponent].push(componentName);

  const data = {
    Component,
    hash: nativeResponse.hash,
    name: componentName,
    children: childrenData,
  };

  cache[componentName] = data;

  return Promise.resolve(data);
}
