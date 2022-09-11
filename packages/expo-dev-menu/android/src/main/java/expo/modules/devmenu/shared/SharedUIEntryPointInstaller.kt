package expo.modules.devmenu.shared

import com.facebook.jni.HybridData
import expo.modules.core.interfaces.DoNotStrip

@Suppress("KotlinJniMissingFunction")
@DoNotStrip
class SharedUIEntryPointInstaller() {
  // Has to be called "mHybridData" - fbjni uses it via reflection
  @DoNotStrip
  private val mHybridData = initHybrid()

  private external fun initHybrid(): HybridData

  external fun install(jsRuntimePointer: Long)
  external fun getRegistryHolder(): Long
  external fun setBoundedRegistryHolder(jsRuntimePointer: Long)

  @Throws(Throwable::class)
  protected fun finalize() {
    mHybridData.resetNative()
  }

  companion object {
    init {
      System.loadLibrary("expo-dev-menu")
    }
  }
}
