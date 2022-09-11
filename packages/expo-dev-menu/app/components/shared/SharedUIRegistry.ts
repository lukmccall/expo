const { SharedUIRegistry } = global;

const cache = {};
const dependencies = {};

export async function getComponentData(componentName, rootComponent = componentName) {
  if (componentName in cache) {
    return cache[componentName];
  }

  const nativeResponse = SharedUIRegistry.getComponentData(componentName);

  // const contex = Promise.all(
  //   nativeResponse.children.map((child) => getComponentData(child, rootComponent))
  // );

  //   const jsThis = convertToContextJSThis(contex);

  //   const Component = Runtime.evaluateJavaScript(nativeResponse.body, jsThis);

  if (!dependencies[rootComponent]) {
    dependencies[rootComponent] = [];
  }

  dependencies[rootComponent].push(componentName);

  return Promise.resolve({
    // Component,
    hash: nativeResponse.hash,
    name: componentName,
    // children: contex,
  });
}
